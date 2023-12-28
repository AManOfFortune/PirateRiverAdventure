#include "renderer_2d.h"

#include "render_command.h"
#include "shader.h"
#include "vertex_array.h"
#include "vertex_buffer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <memory>

struct Renderer2DData
{
    std::shared_ptr<VertexArray> vertexArray;
	std::shared_ptr<Shader> flatColorShader;
};

static Renderer2DData* data;

void Renderer2D::Init()
{
    data = new Renderer2DData();

    data->vertexArray = VertexArray::Create();

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
    data->vertexArray->add_vertex_buffer(vertexBuffer);

    std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(rectangleIndices, sizeof(rectangleIndices) / sizeof(uint32_t));
    data->vertexArray->set_index_buffer(indexBuffer);

    data->flatColorShader = Shader::Create("assets/shaders/flat_color.glsl");
}

void Renderer2D::Shutdown()
{
    delete data;
}

void Renderer2D::BeginScene(const OrthographicCamera& camera)
{
    data->flatColorShader->Bind();
    data->flatColorShader->SetMat4("u_projectionViewMatrix", camera.projection_view_matrix());
}

void Renderer2D::EndScene()
{

}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
    DrawQuad({ position.x, position.y, 0.0f }, size, color);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
    data->flatColorShader->Bind();
    data->flatColorShader->SetFloat4("u_color", color);

    // Calculate the quad transform (model matrix) and set the corresponding uniform in the shader.
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
    data->flatColorShader->SetMat4("u_modelMatrix", transform);

    data->vertexArray->Bind();
    RenderCommand::DrawIndexed(data->vertexArray);
}
