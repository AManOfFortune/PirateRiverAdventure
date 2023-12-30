#include "sandbox_2d_layer.h"

#include "core/core.h"

#include <glm/gtc/matrix_transform.hpp>

Sandbox2DLayer::Sandbox2DLayer()
    : Layer("Sandbox2D"), camera_controller_(1280.0f / 720.0f)
{ }


void Sandbox2DLayer::OnAttach()
{
    texture_ = Texture2D::Create("assets/textures/Checkerboard.png");

    active_scene_ = std::make_shared<Scene>();
    entt::entity entity = active_scene_->CreateEntity();
    active_scene_->registry().emplace<TransformComponent>(entity);
    active_scene_->registry().emplace<SpriteRendererComponent>(entity, glm::vec4{ 0.8f, 0.2f, 0.3f, 1.0f });
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

    active_scene_->OnUpdate(deltaTime);


    Renderer2D::EndScene();
}

void Sandbox2DLayer::OnEvent(Event& event)
{
	camera_controller_.OnEvent(event);
}
