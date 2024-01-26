#include "player.h"
#include "scripts/units/player_mover_script.h"
#include "scripts/game_manager.h"

Player::Player()
{
	color_ = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    inventory_ = std::vector<std::shared_ptr<Item>>();
}

void Player::AttachToScene(std::shared_ptr<Scene> scene)
{
    Entity player = scene->CreateEntity("Player", GetPosition());
    player.AddComponent<SpriteRendererComponent>(GetColor());
    player.AddComponent<ScriptComponent>().Bind<PlayerMoverScript>();

    GameManager::GetInstance().SetPlayer(std::make_shared<Player>(*this));
}

void Player::SetCurrentTile(std::shared_ptr<Tile> tile)
{
    Unit::SetCurrentTile(tile);

    GameManager::GetInstance().SetTileContainingPlayer(tile);
}

void Player::AddItemToInventory(std::shared_ptr<Item> item)
{
	inventory_.push_back(item);
}
