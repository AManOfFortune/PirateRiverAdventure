#pragma once
#include "scripts/units/unit.h"

class Player : public Unit
{
public:
	Player();

	void AttachToScene(std::shared_ptr<Scene> scene) override;
	void OnPlayerMovement(std::shared_ptr<Tile> tile, bool playerMoveEnded) override {};

	void SetCurrentTile(std::shared_ptr<Tile> tile) override;
};

