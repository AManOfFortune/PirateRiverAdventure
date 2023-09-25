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

// Temporary
static GLenum VertexBufferAttributeTypeToGL(VertexBufferAttributeType type)
{
    switch (type)
    {
        case VertexBufferAttributeType::Float:   return GL_FLOAT;
        case VertexBufferAttributeType::Float2:  return GL_FLOAT;
        case VertexBufferAttributeType::Float3:  return GL_FLOAT;
        case VertexBufferAttributeType::Float4:  return GL_FLOAT;
        case VertexBufferAttributeType::Mat3:    return GL_FLOAT;
        case VertexBufferAttributeType::Mat4:    return GL_FLOAT;
        case VertexBufferAttributeType::Int:     return GL_INT;
        case VertexBufferAttributeType::Int2:    return GL_INT;
        case VertexBufferAttributeType::Int3:    return GL_INT;
        case VertexBufferAttributeType::Int4:    return GL_INT;
        case VertexBufferAttributeType::Bool:    return GL_BOOL;
        default: ASSERT(false, "Unknown vertex buffer attribute type!"); return 0;
    }
}

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

    float vertices[7 * 3] = {
        -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
         0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
         0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
    };

    unsigned int indices[3] = {
        0, 1, 2
    };

    // Generate and bind a vertex array.
    glGenVertexArrays(1, &vertex_array_);
    glBindVertexArray(vertex_array_);

    // Create a vertex buffer.
    vertex_buffer_.reset(new VertexBuffer(vertices, sizeof(vertices)));

    {
        VertexBufferLayout layout = {
            { VertexBufferAttributeType::Float3, "a_Position" },
            { VertexBufferAttributeType::Float4, "a_Color" }
        };

        vertex_buffer_->set_layout(layout);
    }

    uint32_t index = 0;
    const VertexBufferLayout& layout = vertex_buffer_->layout();
    for (const auto& attribute : layout)
    {
        // Specify the vertex attribute.
        glVertexAttribPointer(index, 
            attribute.count(), 
            VertexBufferAttributeTypeToGL(attribute.type), 
            attribute.normalized ? GL_TRUE : GL_FALSE, 
            layout.stride(),
            (const void*)attribute.offset);
        // Enable the vertex attribute.
        glEnableVertexAttribArray(index);

        // Update the index.
        index++;
    }

    // Create an index buffer.
    index_buffer_.reset(new IndexBuffer(indices, sizeof(indices) / sizeof(uint32_t)));

    std::string vertexSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
            out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
                v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

    std::string fragmentSource = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
            in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
                color = v_Color;
			}
		)";

    // Create a shader with hardcoded vertex and fragment source code.
    shader_.reset(new Shader(vertexSource, fragmentSource));
}

void Application::Run()
{
    while (is_running_)
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Bind the shader before the draw call.
        shader_->Bind();
        // Bind the vertex array before the draw call.
        glBindVertexArray(vertex_array_);
        // Draw the triangle.
        glDrawElements(GL_TRIANGLES, index_buffer_->count(), GL_UNSIGNED_INT, nullptr);

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