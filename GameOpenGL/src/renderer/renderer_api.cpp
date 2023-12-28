#include "renderer_api.h"

#include <glad/glad.h>

void RendererAPI::Init()
{
    // Enable blending.
    glEnable(GL_BLEND);
    // Set up the blend function.
    // TODO - Add explanation for blend function maths.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

void RendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) const
{
    glDrawElements(GL_TRIANGLES, vertexArray->index_buffer()->count(), GL_UNSIGNED_INT, nullptr);
}
