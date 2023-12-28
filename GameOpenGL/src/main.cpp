#include "core/core.h"
#include "core/events/key_event.h"

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Layer
{
public:
    ExampleLayer()
        : Layer("Example"), camera_controller_(1280.0f / 720.0f, true) // 16:9 aspect ratio
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

        const unsigned int kVertices = 4;
        const unsigned int kPositions = 3;
        const unsigned int kTextureCoords = 2;

        float rectangleVertices[kVertices * (kPositions + kTextureCoords)] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        unsigned int rectangleIndices[6] = {
            0, 1, 2,
            2, 3, 0
        };

        rectangle_vertex_array_.reset(new VertexArray());

        std::shared_ptr<VertexBuffer> rectangleVertexBuffer;
        rectangleVertexBuffer.reset(new VertexBuffer(rectangleVertices, sizeof(rectangleVertices)));

        rectangleVertexBuffer->set_layout({
            { VertexBufferAttributeType::Float3, "a_Position" },
            { VertexBufferAttributeType::Float2, "a_TexCoord" }
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
                uniform mat4 u_modelMatrix;

			    out vec3 v_Position;
                out vec4 v_Color;

			    void main()
			    {
				    v_Position = a_Position;
                    v_Color = a_Color;
				    gl_Position = u_projectionViewMatrix * u_modelMatrix * vec4(a_Position, 1.0);	
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
        shader_ = Shader::Create("VertexPosColor", vertexSource, fragmentSource);

        // Create flat color shader from source file.
        flat_color_shader_ = Shader::Create("assets/shaders/flat_color.glsl");
        // Create texture shader from source file.
        std::shared_ptr<Shader> textureShader = shader_library_.Load("assets/shaders/texture.glsl");

        // Create the checkerboard and logo textures.
        checkerboard_texture_ = std::make_shared<Texture2D>("assets/textures/Checkerboard.png");
        logo_texture_ = std::make_shared<Texture2D>("assets/textures/Mario-Logo.png");

        textureShader->Bind();
        // Set the sampler2D uniform by supplying the bound texture slot (in our case 0).
        textureShader->UploadUniformInt("u_Texture", 0);
    }

    void OnUpdate(DeltaTime deltaTime) override
    {
        // Update the camera controller.
        camera_controller_.OnUpdate(deltaTime);

        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        RenderCommand::Clear();

        // Takes in the camera object which calculates the projection view matrix (P * V) for the whole scene.
        Renderer::BeginScene(camera_controller_.camera());

        glm::mat4 rotation(1.0f);
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
        glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);

        // Render grid.
        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 20; x++)
            {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 translation = glm::translate(glm::mat4(1.0f), pos);
                // Calculate model matrix (M = T * R * S).
                glm::mat4 modelMatrix = translation * rotation * scale;

                if (x % 2 == 0)
                {
                    flat_color_shader_->UploadUniformFloat4("u_color", redColor);
                }
                else
                {
                    flat_color_shader_->UploadUniformFloat4("u_color", blueColor);
                }

                Renderer::Submit(flat_color_shader_, rectangle_vertex_array_, modelMatrix);
            }
        }

        std::shared_ptr<Shader> textureShader = shader_library_.Get("texture");

        // Bind the texture before submitting to renderer.
        checkerboard_texture_->Bind();
        // Render a textured square.
        Renderer::Submit(textureShader, rectangle_vertex_array_, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
        
        logo_texture_->Bind();
        Renderer::Submit(textureShader, rectangle_vertex_array_, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        // Render a triangle.
        // Renderer::Submit(shader_, vertex_array_);

        // Does nothing for now.
        Renderer::EndScene();
    }

    void OnEvent(Event& event) override
    {
        camera_controller_.OnEvent(event);
    }

private:
    ShaderLibrary shader_library_;
    std::shared_ptr<VertexArray> vertex_array_, rectangle_vertex_array_;
    std::shared_ptr<Shader> shader_, flat_color_shader_;
    std::shared_ptr<Texture2D> checkerboard_texture_, logo_texture_;

    OrthographicCameraController camera_controller_;
};

class Sandbox : public Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    }
};

// -- ENTRY POINT -------------------------------

int main(int argc, char** argv)
{
    Log::Initialize();

    LOG_DEBUG("Initialized logger!");

    auto app = new Sandbox;
    app->Run();
    delete app;
}

// ----------------------------------------------
