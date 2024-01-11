#pragma once
#include "scripts/units/unit.h"

class Player : public Unit
{
public:
	Player();

	void AttachToScene(std::shared_ptr<Scene> scene) override;

	void SetPosition(std::shared_ptr<Tile> tile) override;
};

