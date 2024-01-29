#pragma once
#include "scripts/units/unit.h"

class Grunt : public Unit
{
public:
	Grunt(Tile::Direction facingTowards);

	void AttachToScene(std::shared_ptr<Scene> scene) override;
	void OnPlayerMovement(std::shared_ptr<Tile> playerMovedTo, bool playerMovementEnded) override;
	void SetFacingDirection(Tile::Direction direction) override;
	void Reset() override;

private:
	Tile::Direction attackDirection_;
	Tile::Direction initialFacingDirection_;
	int range_ = 1;

	std::shared_ptr<Entity> grunt_;
	bool isDead_ = false;
};

