#include "application.h"

#include "log.h"

#include <functional>
#include <GLFW/glfw3.h>

/// <summary>
/// A temporary example layer to test the layer stack functionality.
/// </summary>
class ExampleLayer : public Layer
{
public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override
    {
        LOG_TRACE("ExampleLayer::OnUpdate");
    }

    void OnEvent(Event& event) override
    {
        LOG_DEBUG("ExampleLayer::OnEvent {0}", event);
    }
};

Application* Application::instance_ = nullptr;

Application::Application()
{
    // The application singleton should only be created once.
    ASSERT(!instance_, "Application singleton already exists!");
    instance_ = this;

    window_ = std::unique_ptr<Window>(Window::Create());
    // Sets the OnEvent method of this instance to be the event callback of the window class.
    // An event triggered in the window class will be handled by the OnEvent method.
    window_->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

    // Push an example layer onto the layer stack.
    PushLayer(new ExampleLayer());
}

Application::~Application()
{

}

void Application::Run()
{
    while (is_running_)
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Iterate through the layer stack from the first to the last layer
        // and call its OnUpdate method. Rendering should happen in this order
        // so that the layers further on top are rendered after the ones at the bottom.
        for (auto it = layer_stack_.begin(); it != layer_stack_.end(); it++)
        {
            (*it)->OnUpdate();
        }
        window_->OnUpdate();
    }
}

void Application::OnEvent(Event& event)
{
    // The event dispatcher is capable of passing an event to a callback with
    // the signature bool fn(Event& event). Only the events of the specified
    // type are propagated to the given callback function/method.
    EventDispatcher dispatcher(event);
    // Here, only events of type WindowCloseEvent are propagated to the OnWindowClose method.
    dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

    LOG_DEBUG("{0}", event);

    // Iterate through the layer stack in reverse order from the last to the first layer
    // and call its OnEvent method. If the event was handled this way by any layer stop
    // propagating it further down the layer stack. Event handling should happen in this 
    // order so that layers on top are able to handle an event before the layers below.
    for (auto it = layer_stack_.rbegin(); it != layer_stack_.rend(); it++)
    {
        (*it)->OnEvent(event);

        if (event.IsHandled())
        {
            break;
        }
    }
}

void Application::PushLayer(Layer* layer)
{
    layer_stack_.PushLayer(layer);
    layer->OnAttach();
}

void Application::PushOverlay(Layer* overlay)
{
    layer_stack_.PushOverlay(overlay);
    overlay->OnAttach();
}

bool Application::OnWindowClose(WindowCloseEvent& event)
{
    is_running_ = false;
    return true;
}

Application* CreateApplication()
{
    return new Application();
}