#pragma once

#include "events/application_event.h"
#include "events/event.h"
#include "layer_stack.h"
#include "window.h"

#include <memory>

/// <summary>
/// This class represents the OpenGL application and should only be instantiated once.
/// </summary>
class Application
{
public:
    Application();
    virtual ~Application();

    inline static Application& Instance() { return *instance_; }

    void Run();
    void OnEvent(Event& event);

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* overlay);

private:
    bool OnWindowClose(WindowCloseEvent& event);

    static Application* instance_;

    std::unique_ptr<Window> window_;
    bool is_running_ = true;
    LayerStack layer_stack_;
};

Application* CreateApplication();