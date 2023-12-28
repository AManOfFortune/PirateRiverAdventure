#include "renderer_2d.h"

#include "render_command.h"
#include "shader.h"
#include "texture.h"
#include "vertex_array.h"
#include "vertex_buffer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <memory>

struct Renderer2DData
{
    std::shared_ptr<VertexArray> vertexArray;
    std::shared_ptr<Shader> textureShader;
    std::shared_ptr<Texture2D> whiteTexture;
};

static Renderer2DData* data;

void Renderer2D::Init()
{
    data = new Renderer2DData();

    data->vertexArray = VertexArray::Create();

    const unsigned int kVertices = 4;
    const unsigned int kPositions = 3;
    const unsigned int kTexCoords = 2;

    float rectangleVertices[kVertices * (kPositions + kTexCoords)] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };

    unsigned int rectangleIndices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(rectangleVertices, sizeof(rectangleVertices));
    vertexBuffer->set_layout({
        { VertexBufferAttributeType::Float3, "a_Position" },
        { VertexBufferAttributeType::Float2, "a_TexCoord" }
    });
    data->vertexArray->add_vertex_buffer(vertexBuffer);

    std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(rectangleIndices, sizeof(rectangleIndices) / sizeof(uint32_t));
    data->vertexArray->set_index_buffer(indexBuffer);

    data->textureShader = Shader::Create("assets/shaders/texture.glsl");
    data->textureShader->Bind();
    data->textureShader->SetInt("u_Texture", 0);

    data->whiteTexture = Texture2D::Create(1, 1);
    // RGBA (255, 255, 255, 255) = 0xffffffff => white.
    uint32_t whiteTextureData = 0xffffffff;
    data->whiteTexture->UploadData(&whiteTextureData, sizeof(uint32_t)); // 4 bytes.
}

void Renderer2D::Shutdown()
{
    delete data;
}

void Renderer2D::BeginScene(const OrthographicCamera& camera)
{
    data->textureShader->Bind();
    data->textureShader->SetMat4("u_ProjectionViewMatrix", camera.projection_view_matrix());
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
    data->textureShader->SetFloat4("u_Color", color);
    data->whiteTexture->Bind();

    // Calculate the quad transform (model matrix) and set the corresponding uniform in the shader.
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
    data->textureShader->SetMat4("u_ModelMatrix", transform);

    data->vertexArray->Bind();
    RenderCommand::DrawIndexed(data->vertexArray);
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture)
{
    DrawQuad({ position.x, position.y, 0.0f }, size, texture);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture)
{
    data->textureShader->SetFloat4("u_Color", glm::vec4(1.0f));
    texture->Bind();

    // Calculate the quad transform (model matrix) and set the corresponding uniform in the shader.
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
    data->textureShader->SetMat4("u_ModelMatrix", transform);

    data->vertexArray->Bind();
    RenderCommand::DrawIndexed(data->vertexArray);
}
