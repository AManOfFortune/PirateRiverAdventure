#include "renderer.h"

Renderer::SceneData* Renderer::sceneData = new Renderer::SceneData;

void Renderer::Init()
{
    RenderCommand::Init();
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
    shader->UploadUniformMat4("u_projectionViewMatrix", sceneData->projectionViewMatrix);
    // Bind the model (M) matrix uniform (also called transform -> position, rotation, scale in world space).
    shader->UploadUniformMat4("u_modelMatrix", transform);
    // In OpenGL the order of binding the shader or vertex array does not matter.
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}

void Renderer::OnWindowResize(uint32_t width, uint32_t height)
{
	RenderCommand::SetViewport(0, 0, width, height);
}
