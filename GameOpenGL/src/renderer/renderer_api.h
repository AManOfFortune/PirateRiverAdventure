#pragma once

#include "vertex_array.h"

#include <glm/glm.hpp>
#include <memory>

/// <summary>
/// The renderer API class holds low level rendering functionality. The implementation of this
/// class would differ depending on the rendering API (e.g. DirectX, Vulkan) used. Because we 
/// only need to worry about OpenGL the differentiation between RendererAPI and Renderer is
/// technically not needed.
/// </summary>
class RendererAPI
{
public:
    void SetClearColor(const glm::vec4& color) const;
    void Clear() const ;
    /// <summary>
    /// Issues a draw call with index buffer data of the associated vertex array.
    /// </summary>
    void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) const;
};