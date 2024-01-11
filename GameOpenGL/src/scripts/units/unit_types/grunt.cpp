#include "grunt.h"
#include "scripts/game_manager.h"

Grunt::Grunt(Tile::Direction facingTowards)
{
	color_ = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	attackDirection_ = facingTowards;
}

void Grunt::AttachToScene(std::shared_ptr<Scene> scene)
{
	Entity grunt = scene->CreateEntity("Grunt", GetPosition());
	grunt.AddComponent<SpriteRendererComponent>(GetColor());
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

void Grunt::PerformAction()
{
}
