#include "renderer_api.h"

#include <glad/glad.h>

std::unique_ptr<RendererAPI> RendererAPI::Create()
{
    return std::make_unique<RendererAPI>();
}

void RendererAPI::Init()
{
    // Enable blending.
    glEnable(GL_BLEND);
    // Set up the blend function.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Enable depth testing using z coordinates determining the draw order.
    glEnable(GL_DEPTH_TEST);
}

void RendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	glViewport(x, y, width, height);
}

void RendererAPI::SetClearColor(const glm::vec4& color) const
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void RendererAPI::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t count) const
{
    uint32_t indexCount = count ? count : vertexArray->index_buffer()->count();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
}
