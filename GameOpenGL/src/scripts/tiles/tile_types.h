#pragma once
#include "tile_factory.h"

class TileGrass : public Tile
{
public:
	TileGrass()
	{
		stringRepresentation_ = 
			"GGG"
			"G G"
			"GGG";

		color_ = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	}
};
REGISTER_TILE_TYPE(TileGrass);

class TileDirt : public Tile
{
public:
	TileDirt()
	{
		stringRepresentation_ =
			"DDD"
			"D D"
			"DDD";

		color_ = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	}
};
REGISTER_TILE_TYPE(TileDirt);

class TilePath : public Tile
{
public:
	TilePath()
	{
		stringRepresentation_ =
			"GGG"
			"- -"
			"GGG";

		color_ = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
};
REGISTER_TILE_TYPE(TilePath);