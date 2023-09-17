#include "application.h"

#include "log.h"

#include <functional>
#include <GLFW/glfw3.h>

Application* Application::instance_ = nullptr;

Application::Application()
{
    // The application singleton should only be created once.
    ASSERT(!instance_, "Application singleton already exists!");
    instance_ = this;

    window_ = std::unique_ptr<Window>(Window::Create());
    // Sets the OnEvent method of this instance to be the event callback of the window class.
    // An event dispatched from the window class will be handled by the OnEvent method.
    window_->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
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
        window_->OnUpdate();
    }
}

void Application::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    // Events of type WindowCloseEvent should invoke the OnWindowClose callback.
    dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
    LOG_DEBUG("{0}", event);
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