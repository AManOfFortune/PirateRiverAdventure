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

    float vertices[7 * 3] = {
        -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
         0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
         0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
    };

    unsigned int indices[3] = {
        0, 1, 2
    };

    // Create a vertex array.
    vertex_array_.reset(new VertexArray());


    // Create a vertex buffer.
    std::shared_ptr<VertexBuffer> vertexBuffer;
    vertexBuffer.reset(new VertexBuffer(vertices, sizeof(vertices)));

    // Create and set a layout for the vertex buffer.
    VertexBufferLayout layout = {
        { VertexBufferAttributeType::Float3, "a_Position" },
        { VertexBufferAttributeType::Float4, "a_Color" }
    };
    vertexBuffer->set_layout(layout);
    
    // Add the vertex buffer after (!) the layout is set.
    vertex_array_->add_vertex_buffer(vertexBuffer);

    // Create an index buffer.
    std::shared_ptr<IndexBuffer> indexBuffer;
    indexBuffer.reset(new IndexBuffer(indices, sizeof(indices) / sizeof(uint32_t)));

    // Set the index buffer.
    vertex_array_->set_index_buffer(indexBuffer);

    rectangle_vertex_array_.reset(new VertexArray());

    float rectangleVertices[4 * 3] = {
        -0.75f, -0.75f, 0.0f,
         0.75f, -0.75f, 0.0f,
         0.75f,  0.75f, 0.0f,
        -0.75f,  0.75f, 0.0f
    };

    unsigned int rectangleIndices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    std::shared_ptr<VertexBuffer> rectangleVertexBuffer;
    rectangleVertexBuffer.reset(new VertexBuffer(rectangleVertices, sizeof(rectangleVertices)));

    rectangleVertexBuffer->set_layout({
        { VertexBufferAttributeType::Float3, "a_Position" }
    });

    rectangle_vertex_array_->add_vertex_buffer(rectangleVertexBuffer);

    std::shared_ptr<IndexBuffer> rectangleIndexBuffer;
    rectangleIndexBuffer.reset(new IndexBuffer(rectangleIndices, sizeof(rectangleIndices) / sizeof(uint32_t)));
    rectangle_vertex_array_->set_index_buffer(rectangleIndexBuffer);

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

    std::string blueVertexSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

    std::string blueFragmentSource = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2f, 0.3f, 0.8f, 1.0f);
			}
		)";

    // Create a shader with hardcoded vertex and fragment source code.
    solid_blue_shader_.reset(new Shader(blueVertexSource, blueFragmentSource));
}

void Application::Run()
{
    while (is_running_)
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        solid_blue_shader_->Bind();
        rectangle_vertex_array_->Bind();
        glDrawElements(GL_TRIANGLES, rectangle_vertex_array_->index_buffer()->count(), GL_UNSIGNED_INT, nullptr);

        // Bind the shader before the draw call.
        shader_->Bind();
        // Bind the vertex array before the draw call.
        vertex_array_->Bind();
        // Draw the triangle.
        glDrawElements(GL_TRIANGLES, vertex_array_->index_buffer()->count(), GL_UNSIGNED_INT, nullptr);

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