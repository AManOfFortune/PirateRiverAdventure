#include "game_manager.h"
#include "levels/level_factory.h"
#include "items/item_types.h"

void GameManager::AddUnitToListeningToPlayerMovement(std::shared_ptr<Unit> unit)
{
	unitsListeningToPlayerMovement_.push_back(unit);
}

void GameManager::NotifyUnitsListeningToPlayerMovement(bool playerMoveEnded)
{
	for (auto unit : unitsListeningToPlayerMovement_)
	{
		unit->OnPlayerMovement(GetTileContainingPlayer(), playerMoveEnded);
	}

	// Pick up item
	std::shared_ptr<Item> itemOnTile = tileContainingPlayer_->GetItemOnTile();
	if(playerMoveEnded && itemOnTile != nullptr && !itemOnTile->IsDecorative())
	{
		player_->AddItemToInventory(itemOnTile);
		itemOnTile->DetachFromScene();
	}

	// Exit level
	if (playerMoveEnded && tileContainingPlayer_->IsExit() && player_->GetItemsOfType<Key>().size() >= currentLevel_->GetKeysRequiredToExit())
	{
		NextLevel();
	}


}

void GameManager::SetTileContainingPlayer(std::shared_ptr<Tile> tile)
{
	tileContainingPlayer_ = tile;
}

void GameManager::SetPlayer(std::shared_ptr<Player> player)
{
	player_ = player;
}

std::shared_ptr<Tile> GameManager::GetTileContainingPlayer() const
{
	return tileContainingPlayer_;
}

std::shared_ptr<Player> GameManager::GetPlayer() const
{
	return player_;
}

void GameManager::StartGame(std::shared_ptr<Scene> activeScene)
{
	activeScene_ = activeScene;
	currentLevel_ = LevelFactory::GetNextLevel();
	currentLevel_->AttachToScene(activeScene_);
}

void GameManager::ResetLevel()
{
	// Reset subscribed units
	unitsListeningToPlayerMovement_.clear();
	// Clear scene
	activeScene_->ClearScene();
	// Reset level
	currentLevel_->Reset();
}

void GameManager::NextLevel()
{
	unitsListeningToPlayerMovement_.clear();
	currentLevel_ = LevelFactory::GetNextLevel();
	activeScene_->ClearScene();
	currentLevel_->AttachToScene(activeScene_);
}
