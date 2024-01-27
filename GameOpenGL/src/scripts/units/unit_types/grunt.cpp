#include "grunt.h"
#include "scripts/game_manager.h"

Grunt::Grunt(Tile::Direction facingTowards)
{
	attackDirection_ = facingTowards;
}

void Grunt::AttachToScene(std::shared_ptr<Scene> scene)
{
	grunt_ = std::make_shared<Entity>(scene->CreateEntity("Grunt", GetPosition()));
	
	// Add sprite renderer component with texture
	auto textureAtlas = Texture2D::Create("assets/textures/NinjaAdventure/Actor/Monsters/Mollusc/Mollusc.png");
	auto textureSize = glm::vec2(16, 16);
	auto textureCoordinates = glm::vec2(0, 0);

	texture_ = SubTexture2D::CreateFromCoords(textureAtlas, textureCoordinates, textureSize);

	grunt_->AddComponent<SpriteRendererComponent>(texture_);
	grunt_->GetComponent<TransformComponent>().SetScale({ 0.5f, 0.5f, 0.5f });

	SetFacingDirection(attackDirection_);
}

void Grunt::OnPlayerMovement(std::shared_ptr<Tile> playerMovedTo, bool playerMovementEnded)
{
	if (playerMovementEnded)
	{
		// Loop all tiles in attack direction
		for (int i = 0; i < range_; i++)
		{
			std::shared_ptr<Tile> attackedTile = GetCurrentTile()->GetConnection(attackDirection_);

			if (attackedTile != nullptr)
			{
				// Check if tile has player
				if (attackedTile == playerMovedTo)
				{
					// TODO: Play attack animation
					// Reset level
					GameManager::GetInstance().ResetLevel();
				}
				
			}
		}
	}
}

void Grunt::SetFacingDirection(Tile::Direction direction)
{
	attackDirection_ = direction;

	if (grunt_ != nullptr)
	{
		auto newTextureCoordinates = glm::vec2(0, 0);

		switch (direction) {
		case Tile::Direction::Top:
			newTextureCoordinates = { 1, 3 };
			break;
		case Tile::Direction::Bottom:
			newTextureCoordinates = { 0, 3 };
			break;
		case Tile::Direction::Left:
			newTextureCoordinates = { 2, 3 };
			break;
		case Tile::Direction::Right:
			newTextureCoordinates = { 3, 3 };
			break;
		}

		auto textureAtlas = Texture2D::Create("assets/textures/NinjaAdventure/Actor/Monsters/Mollusc/Mollusc.png");
		auto textureSize = glm::vec2(16, 16);

		grunt_->GetComponent<SpriteRendererComponent>().SwapTexture(SubTexture2D::CreateFromCoords(textureAtlas, newTextureCoordinates, textureSize));
	}
}
