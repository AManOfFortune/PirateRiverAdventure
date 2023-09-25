#include "application.h"

#include "log/log.h"

#include <functional>

#include <glad/glad.h>

/// <summary>
/// A temporary example layer to test the layer stack functionality.
/// </summary>
class ExampleLayer : public Layer
{
public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override
    {

    }

    void OnEvent(Event& event) override
    {

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

    float vertices[3 * 3] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    unsigned int indices[3] = {
        0, 1, 2
    };

    // Generate and bind a vertex array.
    glGenVertexArrays(1, &vertex_array_);
    glBindVertexArray(vertex_array_);

    // Generate and bind a vertex buffer.
    glGenBuffers(1, &vertex_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    // Set the vertex buffer data.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Generate and bind an element (index) buffer.
    glGenBuffers(1, &element_buffer_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_);
    // Set the element (index) buffer data.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Specify the vertex attributes at location 0.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    // Enable the vertex attributes at location 0.
    glEnableVertexAttribArray(0);
}

Application::~Application()
{

}

void Application::Run()
{
    while (is_running_)
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Bind the vertex array before the draw call.
        glBindVertexArray(vertex_array_);
        // Draw the triangle.
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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
}

void Application::PushOverlay(Layer* overlay)
{
    layer_stack_.PushOverlay(overlay);
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