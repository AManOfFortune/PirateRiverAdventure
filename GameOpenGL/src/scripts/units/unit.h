#pragma once
#include "ecs/scene.h"
#include "ecs/components.h"
#include "scripts/tiles/tile.h"

class Unit
{
public:
	virtual void AttachToScene(std::shared_ptr<Scene> scene) = 0;

	virtual void SetPosition(std::shared_ptr<Tile> tile);
	void SetColor(glm::vec4 color);

	glm::vec3 GetPosition();
	glm::vec4 GetColor();

protected:
	Unit();
	std::shared_ptr<Tile> position_;

	glm::vec4 color_;
	float zOffset_;
};

