#include "player.h"
#include "scripts/units/player_mover_script.h"
#include "scripts/game_manager.h"
#include "renderer/texture.h"

Player::Player(Tile::Direction initialFacingDirection)
{
    inventory_ = std::vector<std::shared_ptr<Item>>();
    facingDirection_ = initialFacingDirection;
}

void Player::AttachToScene(std::shared_ptr<Scene> scene)
{
    player_ = std::make_shared<Entity>(scene->CreateEntity("Player", GetPosition()));

    // Add sprite renderer component with texture
    auto textureAtlas = Texture2D::Create("assets/textures/Boat.png");

    auto textureSize = glm::vec2(32, 16);
    auto textureCoordinates = glm::vec2(0, 0);

    texture_ = SubTexture2D::CreateFromCoords(textureAtlas, textureCoordinates, textureSize);
    
    player_->AddComponent<SpriteRendererComponent>(texture_);
    player_->AddComponent<ScriptComponent>().Bind<PlayerMoverScript>();
    player_->AddComponent<LightComponent>(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);
    player_->GetComponent<TransformComponent>().SetScale({0.7f, 0.35f, 0.35f});

    SetFacingDirection(facingDirection_);

    GameManager::GetInstance().SetPlayer(std::make_shared<Player>(*this));
}

void Player::SetFacingDirection(Tile::Direction direction)
{
    facingDirection_ = direction;

    if (player_ != nullptr) {

        switch (direction) {
        case Tile::Direction::Top:
            player_->GetComponent<TransformComponent>().SetRotation({ 0.0f, 0.0f, -90.0f });
            break;
        case Tile::Direction::Bottom:
            player_->GetComponent<TransformComponent>().SetRotation({ 0.0f, 0.0f, 90.0f });
            break;
        case Tile::Direction::Left:
            player_->GetComponent<TransformComponent>().SetRotation({ 0.0f, 0.0f, 0.0f });
            break;
        case Tile::Direction::Right:
            player_->GetComponent<TransformComponent>().SetRotation({ 0.0f, 180.0f, 0.0f });
            break;
        }
    }

}

void Player::Reset()
{
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
