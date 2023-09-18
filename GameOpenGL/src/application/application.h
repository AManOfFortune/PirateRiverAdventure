#pragma once

#include "events/application_event.h"
#include "events/event.h"
#include "layers/layer_stack.h"
#include "window/window.h"

#include <memory>

/// <summary>
/// This class represents the OpenGL application and should only be instantiated once.
/// </summary>
class Application
{
public:
    Application();
    virtual ~Application();

    /// <summary>
    /// Getter for the static application singleton.
    /// </summary>
    inline static Application& Instance() { return *instance_; }

    /// <summary>
    /// Runs the application.
    /// </summary>
    void Run();
    /// <summary>
    /// Is invoked when a GLFW event is triggered. The event parameter holds the event object
    /// which will be dispatched by the EventDispatcher class and be passed on to the layer stack.
    /// </summary>
    void OnEvent(Event& event);
    /// <summary>
    /// Pushes a new layer onto the layer stack.
    /// </summary>
    void PushLayer(Layer* layer);
    /// <summary>
    /// Pushes a new overlay onto the layer stack. An overlay is similar to a layer,
    /// however an overlay will always be pushed on top of normal layers. This way overlays
    /// could be used to create an UI layer.
    /// </summary>
    /// <param name="overlay"></param>
    void PushOverlay(Layer* overlay);

private:
    /// <summary>
    /// Is invoked when a WindowCloseEvent is triggered.
    /// Stops the running application and should always return true.
    /// </summary>
    bool OnWindowClose(WindowCloseEvent& event);

    static Application* instance_;

    std::unique_ptr<Window> window_;
    bool is_running_ = true;
    LayerStack layer_stack_;
};

Application* CreateApplication();