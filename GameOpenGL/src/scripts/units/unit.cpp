#include "unit.h"

void Unit::SetPosition(std::shared_ptr<Tile> tile)
{
	position_ = tile;
}

void Unit::SetColor(glm::vec4 color)
{
	color_ = color;
}

glm::vec3 Unit::GetPosition()
{
	glm::vec3 position = position_->GetPosition();
	position.z += zOffset_;
	return position;
}

glm::vec4 Unit::GetColor()
{
	return color_;
}

Unit::Unit()
{
	position_ = nullptr;
	color_ = glm::vec4(1.0f);
	zOffset_ = 0.0f;
}
