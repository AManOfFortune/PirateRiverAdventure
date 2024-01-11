#include "game_layer.h"
#include "scripts/camera_controller.h"
#include "renderer/render_command.h"
#include "scripts/levels/level_factory.h"
#include "scripts/game_manager.h"

GameLayer::GameLayer() :
	Layer("GameLayer")
{ }

void GameLayer::OnAttach()
{
    // Create a framebuffer.
    FramebufferSpecification spec;
    // Hardcoded for now.
    spec.width = 1280;
    spec.height = 720;
    framebuffer_ = Framebuffer::Create(spec);

    active_scene_ = std::make_shared<Scene>();
    
    GameManager::GetInstance().StartGame(active_scene_);
}

void GameLayer::OnUpdate(DeltaTime deltaTime)
{
    framebuffer_->Bind();

    RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    RenderCommand::Clear();

    // In here the DrawQuad calls are made.
    active_scene_->OnUpdate(deltaTime);

    framebuffer_->Unbind();
}

void GameLayer::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowResizeEvent>(std::bind(&GameLayer::OnWindowResized, this, std::placeholders::_1));
}

bool GameLayer::OnWindowResized(WindowResizeEvent& event)
{
    active_scene_->OnResize(event.width(), event.height());
    return false;
}
