#pragma once

#include "renderer_api.h"

/// <summary>
/// The render command class is used to access the low level functionality of the renderer
/// API without using it directly. In the future the render command would not be handled 
/// immediately but instead be added to a render command queue. This command queue could
/// then be handled once the renderer scene ended. The command queue would also make 
/// multi-threading possible.
/// </summary>
class RenderCommand
{
public:
    inline static void Init()
    {
        renderer_api_->Init();
    }

    inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
		renderer_api_->SetViewport(x, y, width, height);
	}

    inline static void SetClearColor(const glm::vec4& color)
    {
        renderer_api_->SetClearColor(color);
    }

    inline static void Clear()
    {
        renderer_api_->Clear();
    }

    inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
    {
        renderer_api_->DrawIndexed(vertexArray);
    }

private:
    static RendererAPI* renderer_api_;
};