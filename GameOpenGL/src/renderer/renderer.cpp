#include "renderer.h"

Renderer::SceneData* Renderer::sceneData = new Renderer::SceneData;

void Renderer::BeginScene(OrthographicCamera& camera)
{
    sceneData->projectionViewMatrix = camera.projection_view_matrix();
}

void Renderer::EndScene()
{

}

void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
{
    // It is important to bind the shader first before setting its projection view matrix uniform.
    shader->Bind();
    shader->UploadUniformMat4("u_projectionViewMatrix", sceneData->projectionViewMatrix);
    // In OpenGL the order of binding the shader or vertex array does not matter.
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}
