#include "renderer.h"
#include "renderer_2d.h"

std::shared_ptr<Renderer::SceneData> Renderer::sceneData = std::make_shared<Renderer::SceneData>();

void Renderer::Init()
{
    RenderCommand::Init();
    // Because the 3D renderer is the main renderer we initialize the 2D renderer here.
    Renderer2D::Init();
}

void Renderer::Shutdown()
{
    Renderer2D::Shutdown();
}

void Renderer::BeginScene(OrthographicCamera& camera)
{
    sceneData->projectionViewMatrix = camera.projection_view_matrix();
}

void Renderer::EndScene()
{

}

void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray,
    const glm::mat4& transform)
{
    // It is important to bind the shader first before setting its projection view matrix uniform.
    shader->Bind();
    // Bind the projection view (P * V) matrix uniform.
    shader->SetMat4("u_ProjectionViewMatrix", sceneData->projectionViewMatrix);
    // Bind the model (M) matrix uniform (also called transform -> position, rotation, scale in world space).
    shader->SetMat4("u_ModelMatrix", transform);
    // In OpenGL the order of binding the shader or vertex array does not matter.
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}

void Renderer::OnWindowResize(uint32_t width, uint32_t height)
{
	RenderCommand::SetViewport(0, 0, width, height);
}
