#include "grunt.h"
#include "scripts/game_manager.h"
#include "scripts/items/item_types.h"

Grunt::Grunt(Tile::Direction facingTowards)
{
	initialFacingDirection_ = facingTowards;
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

	SetFacingDirection(initialFacingDirection_);
}

void Grunt::OnPlayerMovement(std::shared_ptr<Tile> playerMovedTo, bool playerMovementEnded)
{
	if (isDead_) return;

	if (playerMovementEnded)
	{
		// Check if player is on same tile as grunt
		if (playerMovedTo == GetCurrentTile())
		{
			// If player has fishing rod, kill grunt
			if (GameManager::GetInstance().GetPlayer()->GetItemsOfType<FishingRod>().size() > 0) 
			{
				grunt_->Destroy();
				isDead_ = true;
				return;
			}
			// Otherwise player dies (reset level)
			else
			{
				GameManager::GetInstance().ResetLevel();
			}
		}

		// Loop all tiles in attack direction
		for (int i = 0; i < range_; i++)
		{
			std::shared_ptr<Tile> attackedTile = GetCurrentTile()->GetConnection(attackDirection_);

			if (attackedTile != nullptr)
			{
				// Check if tile has player
				if (attackedTile == playerMovedTo)
				{
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

void Grunt::Reset()
{
	isDead_ = false;
	//SetFacingDirection(initialFacingDirection_); // BUG: This breaks for some reason, but it doesnt matter since the grunt does not move anyway
}
