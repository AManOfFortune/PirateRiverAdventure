#include "game_layer.h"
#include "scripts/camera_controller.h"

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
    map_ = std::make_shared<Map>();

    camera_entity_ = active_scene_->CreateEntity("Camera");
    camera_entity_.AddComponent<CameraComponent>();

    // Add a script to the camera entity and bind it to the ScriptableEntity subclass CameraController.
    camera_entity_.AddComponent<ScriptComponent>().Bind<CameraController>();
    
    CreateEntities();
}

void GameLayer::OnUpdate(DeltaTime deltaTime)
{
    framebuffer_->Bind();

    RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    RenderCommand::Clear();

    // In here the DrawQuad calls are made.
    active_scene_->OnUpdate(deltaTime);

    Renderer2D::DrawQuad(glm::mat4(1.0f), {1.0f, 1.0f, 1.0f, 1.0f});

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

void GameLayer::CreateEntities()
{
    std::list<std::shared_ptr<Tile>> tiles = map_->parseLevel(map_->level_, map_->levelWidth_, map_->levelHeight_, map_->tileWidth_);

    for (auto& tile : tiles)
	{
		Entity entity = active_scene_->CreateEntity("Tile", tile->getPosition());
		entity.AddComponent<SpriteRendererComponent>(tile->getColor());
	}
}
