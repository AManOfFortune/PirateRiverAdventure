#include "unit.h"
#include "scripts/game_manager.h"

void Unit::SetCurrentTile(std::shared_ptr<Tile> tile)
{
	currentTile_ = tile;
}

void Unit::SetColor(glm::vec4 color)
{
	color_ = color;
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

glm::vec4 Unit::GetColor()
{
	return color_;
}

Unit::Unit()
{
	currentTile_ = nullptr;
	color_ = glm::vec4(1.0f);
	zOffset_ = 0.0f;
}
