#pragma once

#include "events/event.h"

#include "renderer/opengl_context.h"

#include <string>

/// <summary>
/// This struct holds window information needed for instantiation of the window class.
/// </summary>
struct WindowProperties
{
    WindowProperties(const std::string title = "OpenGL Game", unsigned int width = 1280, unsigned int height = 720)
        : title(title), width(width), height(height) {}

    std::string title;
    unsigned int width;
    unsigned int height;
};

/// <summary>
/// This class represents a window and is created by the application.
/// </summary>
class Window
{
public:
    // This EventCallbackFn has the following signature: void fn(Event&)
    using EventCallbackFn = std::function<void(Event&)>;

    Window(const WindowProperties& properties);
    virtual ~Window();
   
    /// <summary>
    /// Factory method to create a window.
    /// </summary>
    static Window* Create(const WindowProperties& properties = WindowProperties());

    /// <summary>
    /// This callback method is called in the applications OnUpdate method.
    /// </summary>
    void OnUpdate();

    /// <summary>
    /// This method specifies which callback function should be invoked when a GLFW event is triggered.  
    /// </summary>
    void SetEventCallback(const EventCallbackFn& callback);

    // Getter for the glfw window.
    inline GLFWwindow* glfw_window() const { return window_; }
    // Getters for width & height.
    inline unsigned int width() const { return data_.width; }
    inline unsigned int height() const { return data_.height; }

private:
    void Initialize(const WindowProperties& properties);
    /// <summary>
    /// Sets GLFW callback methods which trigger our own events.
    /// </summary>
    void SetGlfwCallbacks();
    void Shutdown();

    GLFWwindow* window_;
    OpenGLContext* context_;

    struct WindowData
    {
        std::string title;
        unsigned int width;
        unsigned int height;
        EventCallbackFn callback;
    };

    // This struct is is passed to GLFW with glfwSetWindowUserPointer so that it can be used
    // inside the callback definitions.
    WindowData data_;
};