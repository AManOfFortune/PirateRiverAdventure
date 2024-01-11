#pragma once
#include "scripts/units/unit.h"
#include "scripts/tiles/tile.h"

class Level
{
public:
	virtual ~Level() = default;

	void AttachToScene(std::shared_ptr<Scene> scene);

	std::unordered_map<char, std::shared_ptr<Unit>> GetUnits() { return units_; }

protected:
	Level();
	std::string tileString_;

	int tileWidth_;
	int levelWidth_;

	void AddUnit(char key, std::shared_ptr<Unit> unit);

private:
	std::unordered_map<char, std::shared_ptr<Unit>> units_;

	std::vector<std::shared_ptr<Tile>> ParseLevel(std::string levelString, int width, int tileWidth);
};
