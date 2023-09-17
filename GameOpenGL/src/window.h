#pragma once

#include "events/event.h"

#include <GLFW/glfw3.h>
#include <string>

struct WindowProperties
{
    WindowProperties(const std::string title = "OpenGL Game", unsigned int width = 1280, unsigned int height = 720)
        : title(title), width(width), height(height) {}

    std::string title;
    unsigned int width;
    unsigned int height;
};

class Window
{
public:
    using EventCallbackFn = std::function<void(Event&)>;

    Window(const WindowProperties& properties);
    virtual ~Window();

    static Window* Create(const WindowProperties& properties = WindowProperties());

    void OnUpdate();
    void SetEventCallback(const EventCallbackFn& callback);

    inline unsigned int width() const { return data_.width; }
    inline unsigned int height() const { return data_.height; }

private:
    void Initialize(const WindowProperties& properties);
    void SetGlfwCallbacks();
    void Shutdown();

    GLFWwindow* window_;

    struct WindowData
    {
        std::string title;
        unsigned int width;
        unsigned int height;
        EventCallbackFn callback;
    };

    WindowData data_;
};