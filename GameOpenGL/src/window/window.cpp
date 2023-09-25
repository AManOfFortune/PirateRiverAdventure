#include "window.h"

#include "core.h"
#include "events/application_event.h"
#include "events/key_event.h"
#include "events/mouse_event.h"
#include "log/log.h"

#include <GLFW/glfw3.h>

static bool isGlfwInitialized = false;

static void OnGlfwError(int error, const char* description)
{
    LOG_ERROR("GLFW Error ({0}): {1}", error, description);
}

Window* Window::Create(const WindowProperties& properties)
{
    return new Window(properties);
}

Window::Window(const WindowProperties& properties)
{
    Initialize(properties);
}

Window::~Window()
{
    Shutdown();
}

void Window::OnUpdate()
{
    glfwPollEvents();
    context_->SwapBuffers();
}

void Window::SetEventCallback(const EventCallbackFn& callback)
{
    data_.callback = callback;
}

void Window::Initialize(const WindowProperties& properties)
{
    data_.title = properties.title;
    data_.width = properties.width;
    data_.height = properties.height;

    LOG_DEBUG("Creating window {0} ({1}, {2})!", data_.title, data_.width, data_.height);

    if (!isGlfwInitialized)
    {
        int success = glfwInit();
        ASSERT(success, "GLFW could not be initialized!");

        // Specifies the OpenGL version and profile (3.3 Core).
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // Sets the callback function in case of a GLFW error.
        glfwSetErrorCallback(OnGlfwError);

        isGlfwInitialized = true;
    }

    window_ = glfwCreateWindow((int)data_.width, (int)data_.height, data_.title.c_str(), nullptr, nullptr);
    
    context_ = new Context(window_);
    context_->Initialize();
    
    // Set the user pointer (data_) which is stored until the window is destroyed.
    glfwSetWindowUserPointer(window_, &data_);

    SetGlfwCallbacks();
}

// This method sets GLFW callback functions creates our own event objects and invokes the method Application::OnEvent(Event&).
void Window::SetGlfwCallbacks()
{
    glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int width, int height) 
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        data.width = width;
        data.height = height;

        WindowResizeEvent event(width, height);
        data.callback(event);
    });

    glfwSetWindowCloseCallback(window_, [](GLFWwindow* window) 
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.callback(event);
    });

    glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods) 
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action) 
        {
            case GLFW_PRESS: 
            {
                KeyPressedEvent event(key, 0);
                data.callback(event);
                break;
            }
            case GLFW_RELEASE: 
            {
                KeyReleasedEvent event(key);
                data.callback(event);
                break;
            }
            case GLFW_REPEAT: 
            {
                KeyPressedEvent event(key, 1);
                data.callback(event);
                break;
            }
        }
    });

    glfwSetCharCallback(window_, [](GLFWwindow* window, unsigned int key)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        KeyTypedEvent event(key);
        data.callback(event);
    });

    glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods) 
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action) 
        {
            case GLFW_PRESS: 
            {
                MouseButtonPressedEvent event(button);
                data.callback(event);
                break;
            }
            case GLFW_RELEASE: 
            {
                MouseButtonReleasedEvent event(button);
                data.callback(event);
                break;
            }
        }
    });

    glfwSetScrollCallback(window_, [](GLFWwindow* window, double xOffset, double yOffset) 
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.callback(event);
    });

    glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double xPos, double yPos) 
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseMovedEvent event((float)xPos, (float)yPos);
        data.callback(event);
    });
}

void Window::Shutdown()
{
    glfwDestroyWindow(window_);
}