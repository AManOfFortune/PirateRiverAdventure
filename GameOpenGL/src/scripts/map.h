#pragma once

#include <string>
#include "tiles/tile_types.h"

class Map
{
public:
	Map() {
		level_ = 
			"GGGGGGGGGGGGGGG"
			"G GG GG G- -G G"
			"GGGGGGGGGGGGGGG"
			"GGGGGGGGGGGGGGG"
			"G G- -- -- -G G"
			"GGGGGGGGGGGGGGG"
			"GGGGGGGGGGGGGGG"
			"G G- -G G- -G G"
			"GGGGGGGGGGGGGGG";
		levelWidth_ = 5;
		levelHeight_ = 3;
		tileWidth_ = 3;

	};

	std::list<std::shared_ptr<Tile>> parseLevel(std::string levelString, int width, int height, int tileWidth)
	{
		std::list<std::shared_ptr<Tile>> result;
		
		for (int i = 0, posCounter = 0; i < levelString.length(); i += tileWidth, posCounter++) {
			std::string currentTile = levelString.substr(i, tileWidth) + levelString.substr(i + (width * tileWidth), tileWidth) + levelString.substr(i + (width * tileWidth * 2), tileWidth);

			float posX = posCounter%width;
			float posY = -(posCounter/width);

			glm::vec3 tilePosition = glm::vec3(posX, posY, 1.0f);

			std::shared_ptr<Tile> tile = TileFactory::createTile(currentTile);
			tile->setPosition(tilePosition);
			
			result.push_back(tile);

			if((i + tileWidth) % (width * tileWidth) == 0 && i != 0) {
				i += (width * tileWidth * 2);
			}
		}

		return result;
	};

	std::string level_;
	int levelWidth_;
	int levelHeight_;
	int tileWidth_;
};