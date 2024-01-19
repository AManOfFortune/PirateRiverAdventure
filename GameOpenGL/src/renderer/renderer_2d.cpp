#include "renderer_2d.h"

#include "camera.h"
#include "render_command.h"
#include "shader.h"
#include "texture.h"
#include "vertex_array.h"
#include "vertex_buffer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <memory>

struct QuadVertex
{
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texCoord;
    float texIndex;
    float tilingFactor;
};

struct Renderer2DData
{
    static const uint32_t maxQuads = 20000;
    static const uint32_t maxVertices = maxQuads * 4;
    static const uint32_t maxIndices = maxQuads * 6;
    static const uint32_t maxTextureSlots = 32;

    std::shared_ptr<VertexArray> quadVertexArray;
    std::shared_ptr<VertexBuffer> quadVertexBuffer;
    std::shared_ptr<Shader> textureShader;
    std::shared_ptr<Texture2D> whiteTexture;

    uint32_t quadIndexCount = 0;
    QuadVertex* quadVertexBufferBase = nullptr;
    QuadVertex* quadVertexBufferPtr = nullptr;

    std::array<std::shared_ptr<SubTexture2D>, maxTextureSlots> textureSlots;
    uint32_t textureSlotIndex = 1; // 0 = white texture.

    glm::vec4 quadVertexPositions[4] = {
        { -0.5f, -0.5f, 0.0f, 1.0f },
        { 0.5f, -0.5f, 0.0f, 1.0f },
	    { 0.5f,  0.5f, 0.0f, 1.0f },
	    { -0.5f,  0.5f, 0.0f, 1.0f }
    };
};

static Renderer2DData data;

void Renderer2D::Init()
{
    data.quadVertexArray = VertexArray::Create();

    data.quadVertexBuffer = VertexBuffer::Create(data.maxVertices * sizeof(QuadVertex));
    data.quadVertexBuffer->set_layout({
        { VertexBufferAttributeType::Float3, "a_Position" },
        { VertexBufferAttributeType::Float4, "a_Color" },
        { VertexBufferAttributeType::Float2, "a_TexCoord" },
        { VertexBufferAttributeType::Float, "a_TexIndex" },
        { VertexBufferAttributeType::Float, "a_TilingFactor" },
        });
    data.quadVertexArray->add_vertex_buffer(data.quadVertexBuffer);

    data.quadVertexBufferBase = new QuadVertex[data.maxVertices];

    uint32_t* quadIndices = new uint32_t[data.maxIndices];

    uint32_t offset = 0;
    for (uint32_t i = 0; i < data.maxIndices; i += 6)
    {
        quadIndices[i + 0] = offset + 0;
        quadIndices[i + 1] = offset + 1;
        quadIndices[i + 2] = offset + 2;

        quadIndices[i + 3] = offset + 2;
        quadIndices[i + 4] = offset + 3;
        quadIndices[i + 5] = offset + 0;

        offset += 4;
    }

    std::shared_ptr<IndexBuffer> quadIndexBuffer = IndexBuffer::Create(quadIndices, data.maxIndices);
    data.quadVertexArray->set_index_buffer(quadIndexBuffer);
    delete[] quadIndices;

    data.whiteTexture = Texture2D::Create(1, 1);
    // RGBA (255, 255, 255, 255) = 0xffffffff => white.
    uint32_t whiteTextureData = 0xffffffff;
    data.whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t)); // 4 bytes.

    int32_t samplers[data.maxTextureSlots];
    for (uint32_t i = 0; i < data.maxTextureSlots; i++)
    {
        samplers[i] = i;
    }
    data.textureShader = Shader::Create("assets/shaders/texture.glsl");
    data.textureShader->Bind();
    data.textureShader->SetIntArray("u_Textures", samplers, data.maxTextureSlots);

    data.textureSlots[0] = SubTexture2D::Create(data.whiteTexture, { 0.0f, 0.0f }, { 1.0f, 1.0f });

    data.quadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
    data.quadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
    data.quadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
    data.quadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
}

void Renderer2D::Shutdown()
{
    delete[] data.quadVertexBufferBase;
}

void Renderer2D::BeginScene(const Camera& camera, const glm::mat4& transform)
{
    glm::mat4 projectionViewMatrix = camera.projection() * glm::inverse(transform);

    data.textureShader->Bind();
	data.textureShader->SetMat4("u_ProjectionViewMatrix", projectionViewMatrix);

    data.quadIndexCount = 0;
	data.quadVertexBufferPtr = data.quadVertexBufferBase;

	data.textureSlotIndex = 1;
}

void Renderer2D::BeginScene(const OrthographicCamera& camera)
{
    data.textureShader->Bind();
    data.textureShader->SetMat4("u_ProjectionViewMatrix", camera.projection_view_matrix());

    data.quadIndexCount = 0;
    data.quadVertexBufferPtr = data.quadVertexBufferBase;

    data.textureSlotIndex = 1;
}

void Renderer2D::EndScene()
{
    uint32_t size = (uint32_t)((uint8_t*)data.quadVertexBufferPtr - (uint8_t*)data.quadVertexBufferBase);
    data.quadVertexBuffer->SetData(data.quadVertexBufferBase, size);

    Flush();
}

void Renderer2D::Flush()
{
    if (data.quadIndexCount == 0)
    {
		return;
	}

    for (uint32_t i = 0; i < data.textureSlotIndex; i++)
    {
		data.textureSlots[i]->Bind(i);
	}

	RenderCommand::DrawIndexed(data.quadVertexArray, data.quadIndexCount);
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
    DrawQuad({ position.x, position.y, 0.0f }, size, color);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
    DrawQuad(transform, color);
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, const Texture2DProperties& textureProperties)
{
    DrawQuad({ position.x, position.y, 0.0f }, size, texture, textureProperties);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, const Texture2DProperties& textureProperties)
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
    DrawQuad(transform, texture, textureProperties);
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<SubTexture2D>& sub, const Texture2DProperties& textureProperties)
{
    DrawQuad({ position.x, position.y, 0.0f }, size, sub, textureProperties);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<SubTexture2D>& sub, const Texture2DProperties& textureProperties)
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
    DrawQuad(transform, sub, textureProperties);
}

void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
{
    constexpr size_t quadVertexCount = 4;
    const float textureIndex = 0.0f; // White texture index.
    constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
    const float tilingFactor = 1.0f;

    if (data.quadIndexCount >= Renderer2DData::maxIndices)
    {
		FlushAndReset();
	}

    for (size_t i = 0; i < quadVertexCount; i++)
    {
        data.quadVertexBufferPtr->position = transform * data.quadVertexPositions[i];
        data.quadVertexBufferPtr->color = color;
        data.quadVertexBufferPtr->texCoord = textureCoords[i];
        data.quadVertexBufferPtr->texIndex = textureIndex;
        data.quadVertexBufferPtr->tilingFactor = tilingFactor;
        data.quadVertexBufferPtr++;
    }

    data.quadIndexCount += 6;
}

void Renderer2D::DrawQuad(const glm::mat4& transform, const std::shared_ptr<Texture2D>& texture, const Texture2DProperties& textureProperties)
{
    constexpr size_t quadVertexCount = 4;
    constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

    if (data.quadIndexCount >= Renderer2DData::maxIndices)
    {
        FlushAndReset();
    }

    float textureIndex = 0.0f;
    for (uint32_t i = 1; i < data.textureSlotIndex; i++)
    {
        if (*data.textureSlots[i]->texture() == *texture)
        {
            textureIndex = (float)i;
            break;
        }
    }

    if (textureIndex == 0.0f)
    {
        if (data.textureSlotIndex >= Renderer2DData::maxTextureSlots)
        {
			FlushAndReset();
		}

		textureIndex = (float)data.textureSlotIndex;
        data.textureSlots[data.textureSlotIndex] = SubTexture2D::Create(texture, { 0.0f, 0.0f }, { 1.0f, 1.0f });
		data.textureSlotIndex++;
    }

    for (size_t i = 0; i < quadVertexCount; i++)
    {
        data.quadVertexBufferPtr->position = transform * data.quadVertexPositions[i];
        data.quadVertexBufferPtr->color = textureProperties.tintColor;
        data.quadVertexBufferPtr->texCoord = textureCoords[i];
        data.quadVertexBufferPtr->texIndex = textureIndex;
        data.quadVertexBufferPtr->tilingFactor = textureProperties.tilingFactor;
        data.quadVertexBufferPtr++;
    }

    data.quadIndexCount += 6;
}

void Renderer2D::DrawQuad(const glm::mat4& transform, const std::shared_ptr<SubTexture2D>& sub, const Texture2DProperties& textureProperties)
{
    constexpr size_t quadVertexCount = 4;

    if (data.quadIndexCount >= Renderer2DData::maxIndices)
    {
        FlushAndReset();
    }

    float textureIndex = 0.0f;
    for (uint32_t i = 1; i < data.textureSlotIndex; i++)
    {
        if (*data.textureSlots[i]->texture() == *sub->texture())
        {
            textureIndex = (float)i;
            break;
        }
    }

    if (textureIndex == 0.0f)
    {
        if (data.textureSlotIndex >= Renderer2DData::maxTextureSlots)
        {
            FlushAndReset();
        }

        textureIndex = (float)data.textureSlotIndex;
        data.textureSlots[data.textureSlotIndex] = sub;
        data.textureSlotIndex++;
    }

    for (size_t i = 0; i < quadVertexCount; i++)
    {
        data.quadVertexBufferPtr->position = transform * data.quadVertexPositions[i];
        data.quadVertexBufferPtr->color = textureProperties.tintColor;
        data.quadVertexBufferPtr->texCoord = sub->texture_coords()[i];
        data.quadVertexBufferPtr->texIndex = textureIndex;
        data.quadVertexBufferPtr->tilingFactor = textureProperties.tilingFactor;
        data.quadVertexBufferPtr++;
    }

    data.quadIndexCount += 6;
}

void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
{
    DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
}

void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) 
        * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
        * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
    DrawQuad(transform, color);
}

void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, const Texture2DProperties& textureProperties)
{
    DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, textureProperties);
}

void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, const Texture2DProperties& textureProperties)
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
        * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
        * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });    
    DrawQuad(transform, texture, textureProperties);
}

void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const std::shared_ptr<SubTexture2D>& sub, const Texture2DProperties& textureProperties)
{
    DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, sub, textureProperties);
}

void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const std::shared_ptr<SubTexture2D>& sub, const Texture2DProperties& textureProperties)
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
        * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
        * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
    DrawQuad(transform, sub, textureProperties);
}

void Renderer2D::FlushAndReset()
{
    EndScene();
    
	data.quadIndexCount = 0;
	data.quadVertexBufferPtr = data.quadVertexBufferBase;

	data.textureSlotIndex = 1;
}