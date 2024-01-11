#include "game_manager.h"
#include "levels/level_factory.h"

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
}

void GameManager::SetTileContainingPlayer(std::shared_ptr<Tile> tile)
{
	tileContainingPlayer_ = tile;
}

std::shared_ptr<Tile> GameManager::GetTileContainingPlayer() const
{
	return tileContainingPlayer_;
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
	currentLevel_->AttachToScene(activeScene_);
}
