#include "game_manager.h"

void GameManager::SetTileContainingPlayer(std::shared_ptr<Tile> tile)
{
	tileContainingPlayer_ = tile;
}

std::shared_ptr<Tile> GameManager::GetTileContainingPlayer() const
{
	return tileContainingPlayer_;
}
