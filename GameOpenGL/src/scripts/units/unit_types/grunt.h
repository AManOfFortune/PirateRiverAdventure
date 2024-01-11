#pragma once
#include "scripts/units/unit.h"

class Grunt : public Unit
{
public:
	Grunt(Tile::Direction facingTowards);

	void AttachToScene(std::shared_ptr<Scene> scene) override;
	void OnPlayerMovement(std::shared_ptr<Tile> playerMovedTo, bool playerMovementEnded) override;

private:
	Tile::Direction attackDirection_;
	int range_ = 1;
};

