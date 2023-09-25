#include "renderer_api.h"

#include <glad/glad.h>

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
