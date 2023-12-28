#include "sandbox_2d_layer.h"

#include "core/core.h"

#include <glm/gtc/matrix_transform.hpp>

Sandbox2DLayer::Sandbox2DLayer()
    : Layer("Sandbox2D"), camera_controller_(1280.0f / 720.0f)
{ }


void Sandbox2DLayer::OnAttach()
{
    texture_ = Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2DLayer::OnDetach()
{

}

void Sandbox2DLayer::OnUpdate(DeltaTime deltaTime)
{
	camera_controller_.OnUpdate(deltaTime);

    RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    RenderCommand::Clear();

    Renderer2D::BeginScene(camera_controller_.camera());

    Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.5f, 0.5f }, { 0.8f, 0.2f, 0.3f, 1.0f });
    Renderer2D::DrawQuad({  1.0f, 0.0f }, { 0.5f, 0.5f }, { 0.2f, 0.3f, 0.8f, 1.0f });
    // The z value is used to determine draw order. OpenGL uses a right-handed coordinate system.
    // This means that the positive z-axis points out of the screen.
    Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, texture_);  

    Renderer2D::EndScene();
}

void Sandbox2DLayer::OnEvent(Event& event)
{
	camera_controller_.OnEvent(event);
}
