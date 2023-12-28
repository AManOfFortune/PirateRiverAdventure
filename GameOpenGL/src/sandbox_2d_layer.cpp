#include "sandbox_2d_layer.h"

#include "renderer/renderer.h"

#include <glm/gtc/matrix_transform.hpp>

Sandbox2DLayer::Sandbox2DLayer()
    : Layer("Sandbox2D"), camera_controller_(1280.0f / 720.0f)
{ }


void Sandbox2DLayer::OnAttach()
{
    vertex_array_ = VertexArray::Create();

    const unsigned int kVertices = 4;
    const unsigned int kPositions = 3;

    float rectangleVertices[kVertices * kPositions] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
    };

    unsigned int rectangleIndices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(rectangleVertices, sizeof(rectangleVertices));
    vertexBuffer->set_layout({
        { VertexBufferAttributeType::Float3, "a_Position" }        
    });
    vertex_array_->add_vertex_buffer(vertexBuffer);

    std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(rectangleIndices, sizeof(rectangleIndices) / sizeof(uint32_t));
    vertex_array_->set_index_buffer(indexBuffer);

    flat_color_shader_ = Shader::Create("assets/shaders/flat_color.glsl");
}

void Sandbox2DLayer::OnDetach()
{

}

void Sandbox2DLayer::OnUpdate(DeltaTime deltaTime)
{
	camera_controller_.OnUpdate(deltaTime);

    RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    RenderCommand::Clear();

    Renderer::BeginScene(camera_controller_.camera());

    flat_color_shader_->Bind();
    flat_color_shader_->UploadUniformFloat4("u_color", glm::vec4({ 0.0f, 0.2f, 0.8f, 1.0f }));
    Renderer::Submit(flat_color_shader_, vertex_array_, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    Renderer::EndScene();
}

void Sandbox2DLayer::OnEvent(Event& event)
{
	camera_controller_.OnEvent(event);
}
