#include "unit.h"
#include "scripts/game_manager.h"

void Unit::SetCurrentTile(std::shared_ptr<Tile> tile)
{
	currentTile_ = tile;
}

std::shared_ptr<Tile> Unit::GetCurrentTile()
{
	return currentTile_;
}

glm::vec3 Unit::GetPosition()
{
	glm::vec3 position = currentTile_->GetPosition();
	position.z += zOffset_;
	return position;
}

Unit::Unit()
{
	currentTile_ = nullptr;
	texture_ = nullptr;
	zOffset_ = 0.0f;
}
