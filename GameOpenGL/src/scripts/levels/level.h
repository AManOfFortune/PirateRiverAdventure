#pragma once
#include "scripts/units/unit.h"
#include "scripts/tiles/tile.h"
#include "scripts/items/item.h"

class Level
{
public:
	virtual ~Level() = default;

	void AttachToScene(std::shared_ptr<Scene> scene);
	void Reset();

	std::unordered_map<char, std::shared_ptr<Unit>> GetUnits() { return activeUnits_; }
	int GetKeysRequiredToExit() { return keysRequiredToExit_; }

protected:
	Level();
	std::string tileString_;

	int tileWidth_;
	int levelWidth_;
	int keysRequiredToExit_;

	std::shared_ptr<Scene> scene_;

	void AddUnit(char key, std::shared_ptr<Unit> unit);
	void AddItem(char key, std::shared_ptr<Item> item);

private:
	std::unordered_map<char, std::shared_ptr<Unit>> unitAtlas_;
	std::unordered_map<char, std::shared_ptr<Unit>> activeUnits_;
	std::unordered_map<char, std::shared_ptr<Item>> items_;

	std::vector<std::shared_ptr<Tile>> ParseLevel(std::string levelString, int width, int tileWidth);
};
