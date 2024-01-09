#pragma once

#include <string>
#include "tiles/tile_types.h"

class LevelData
{
public:
	LevelData();

	std::vector<std::shared_ptr<Tile>> GetNextLevel();

private:
	
	std::vector<std::shared_ptr<Tile>> ParseLevel(std::string levelString, int width, int tileWidth);

	std::string level_;
	int tileWidth_;
	int levelWidth_;
};