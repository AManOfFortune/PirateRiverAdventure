#include "game_layer.h"

GameLayer::GameLayer() :
	Layer("GameLayer"), camera_controller_(1280.0f / 720.0f)
{ }

void GameLayer::OnAttach()
{
    active_scene_ = std::make_shared<Scene>();
    map_ = std::make_shared<Map>();
    
    CreateEntities();

    //Entity square_entity = active_scene_->CreateEntity("Square");
    //square_entity.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.8f, 0.2f, 0.3f, 1.0f });
}

void GameLayer::OnUpdate(DeltaTime deltaTime)
{
    camera_controller_.OnUpdate(deltaTime);

    RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    RenderCommand::Clear();

    Renderer2D::BeginScene(camera_controller_.camera());

    // In here the DrawQuad calls are made.
    active_scene_->OnUpdate(deltaTime);

    Renderer2D::EndScene();
}

void GameLayer::OnEvent(Event& event)
{
    camera_controller_.OnEvent(event);
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
