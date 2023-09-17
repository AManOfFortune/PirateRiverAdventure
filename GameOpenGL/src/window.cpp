#include "window.h"

#include "core.h"
#include "log.h"

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
    glfwSwapBuffers(window_);
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

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwSetErrorCallback(OnGlfwError);

        isGlfwInitialized = true;
    }

    window_ = glfwCreateWindow((int)data_.width, (int)data_.height, data_.title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window_);
    glfwSetWindowUserPointer(window_, &data_);

    SetGlfwCallbacks();
}

void Window::SetGlfwCallbacks()
{

}

void Window::Shutdown()
{
    glfwDestroyWindow(window_);
}