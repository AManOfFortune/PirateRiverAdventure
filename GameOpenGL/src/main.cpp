#include "core.h"
#include "events/key_event.h"

class ExampleLayer : public Layer
{
public:
    ExampleLayer()
        : Layer("Example"), camera_(-1.6f, 1.6f, -0.9f, 0.9f)
    {
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

        rectangle_vertex_array_.reset(new VertexArray());

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

                uniform mat4 u_projectionViewMatrix;

			    out vec3 v_Position;
                out vec4 v_Color;

			    void main()
			    {
				    v_Position = a_Position;
                    v_Color = a_Color;
				    gl_Position = u_projectionViewMatrix * vec4(a_Position, 1.0);	
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

                uniform mat4 u_projectionViewMatrix;

			    out vec3 v_Position;

			    void main()
			    {
				    v_Position = a_Position;
				    gl_Position = u_projectionViewMatrix * vec4(a_Position, 1.0);	
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

    void OnUpdate() override
    {
        if (Input::IsKeyPressed(CG_KEY_LEFT))
            camera_pos_.x -= camera_speed_;
        else if (Input::IsKeyPressed(CG_KEY_RIGHT))
            camera_pos_.x += camera_speed_;

        if (Input::IsKeyPressed(CG_KEY_DOWN))
            camera_pos_.y -= camera_speed_;
        else if (Input::IsKeyPressed(CG_KEY_UP))
            camera_pos_.y += camera_speed_;

        if (Input::IsKeyPressed(CG_KEY_A))
            camera_rot_ += camera_rot_speed_;
        else if (Input::IsKeyPressed(CG_KEY_D))
            camera_rot_ -= camera_rot_speed_;

        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        RenderCommand::Clear();

        // Test setting the camera position and rotation.
        camera_.set_position(camera_pos_);
        camera_.set_rotation(camera_rot_);

        // Does nothing for now.
        Renderer::BeginScene(camera_);

        Renderer::Submit(solid_blue_shader_, rectangle_vertex_array_);
        Renderer::Submit(shader_, vertex_array_);

        // Does nothing for now.
        Renderer::EndScene();
    }

    void OnEvent(Event& event) override
    {

    }

private:
    std::shared_ptr<VertexArray> vertex_array_;
    std::shared_ptr<Shader> shader_;
    std::shared_ptr<VertexArray> rectangle_vertex_array_;
    std::shared_ptr<Shader> solid_blue_shader_;

    OrthographicCamera camera_;

    glm::vec3 camera_pos_ = { 0.0f, 0.0f, 0.0f };
    float camera_speed_ = 0.01f;

    float camera_rot_ = 0.0f;
    float camera_rot_speed_ = 0.1f;
};

class Sandbox : public Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    }
};

int main(int argc, char** argv)
{
    Log::Initialize();

    LOG_DEBUG("Initialized logger!");

    auto app = new Sandbox;
    app->Run();
    delete app;
}