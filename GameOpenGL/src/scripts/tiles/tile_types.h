#pragma once

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

// Dead ends
class TilePathLeft : public Tile
{
public:
	TilePathLeft()
	{
		stringRepresentation_ =
			"GGG"
			"- G"
			"GGG";

		color_ = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		isWalkable_[Left] = true;
	}
};
REGISTER_TILE_TYPE(TilePathLeft);

class TilePathRight : public Tile
{
public:
	TilePathRight()
	{
		stringRepresentation_ =
			"GGG"
			"G -"
			"GGG";

		color_ = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		isWalkable_[Right] = true;
	}
};
REGISTER_TILE_TYPE(TilePathRight);

class TilePathTop : public Tile
{
public:
	TilePathTop()
	{
		stringRepresentation_ =
			"G|G"
			"G G"
			"GGG";

		color_ = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		isWalkable_[Top] = true;
	}
};
REGISTER_TILE_TYPE(TilePathTop);

class TilePathBottom : public Tile
{
public:
	TilePathBottom()
	{
		stringRepresentation_ =
			"GGG"
			"G G"
			"G|G";

		color_ = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		isWalkable_[Bottom] = true;
	}
};
REGISTER_TILE_TYPE(TilePathBottom);

// Straights
class TilePathLeftRight : public Tile
{
public:
	TilePathLeftRight()
	{
		stringRepresentation_ =
			"GGG"
			"- -"
			"GGG";

		color_ = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		isWalkable_[Left] = true;
		isWalkable_[Right] = true;
	}
};
REGISTER_TILE_TYPE(TilePathLeftRight);

class TilePathTopBottom : public Tile
{
public:
	TilePathTopBottom()
	{
		stringRepresentation_ =
			"G|G"
			"G G"
			"G|G";

		color_ = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		isWalkable_[Top] = true;
		isWalkable_[Bottom] = true;
	}
};
REGISTER_TILE_TYPE(TilePathTopBottom);

// Corners
class TilePathTopRight : public Tile
{
public:
	TilePathTopRight()
	{
		stringRepresentation_ =
			"G|G"
			"G -"
			"GGG";

		color_ = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		isWalkable_[Top] = true;
		isWalkable_[Right] = true;
	}
};
REGISTER_TILE_TYPE(TilePathTopRight);

class TilePathTopLeft : public Tile
{
public:
	TilePathTopLeft()
	{
		stringRepresentation_ =
			"G|G"
			"- G"
			"GGG";

		color_ = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		isWalkable_[Top] = true;
		isWalkable_[Left] = true;
	}
};
REGISTER_TILE_TYPE(TilePathTopLeft);

class TilePathBottomRight : public Tile
{
public:
	TilePathBottomRight()
	{
		stringRepresentation_ =
			"GGG"
			"G -"
			"G|G";

		color_ = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		isWalkable_[Bottom] = true;
		isWalkable_[Right] = true;
	}
};
REGISTER_TILE_TYPE(TilePathBottomRight);

class TilePathBottomLeft : public Tile
{
public:
	TilePathBottomLeft()
	{
		stringRepresentation_ =
			"GGG"
			"- G"
			"G|G";

		color_ = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		isWalkable_[Bottom] = true;
		isWalkable_[Left] = true;
	}
};
REGISTER_TILE_TYPE(TilePathBottomLeft);

// T's
class TilePathTopLeftRight : public Tile
{
public:
	TilePathTopLeftRight()
	{
		stringRepresentation_ =
			"G|G"
			"- -"
			"GGG";

		color_ = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

		isWalkable_[Top] = true;
		isWalkable_[Left] = true;
		isWalkable_[Right] = true;
	}
};
REGISTER_TILE_TYPE(TilePathTopLeftRight);

class TilePathBottomLeftRight : public Tile
{
public:
	TilePathBottomLeftRight()
	{
		stringRepresentation_ =
			"GGG"
			"- -"
			"G|G";

		color_ = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

		isWalkable_[Bottom] = true;
		isWalkable_[Left] = true;
		isWalkable_[Right] = true;
	}
};
REGISTER_TILE_TYPE(TilePathBottomLeftRight);

class TilePathTopBottomRight : public Tile
{
public:
	TilePathTopBottomRight()
	{
		stringRepresentation_ =
			"G|G"
			"G -"
			"G|G";

		color_ = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

		isWalkable_[Top] = true;
		isWalkable_[Bottom] = true;
		isWalkable_[Right] = true;
	}
};
REGISTER_TILE_TYPE(TilePathTopBottomRight);

class TilePathTopBottomLeft : public Tile
{
public:
	TilePathTopBottomLeft()
	{
		stringRepresentation_ =
			"G|G"
			"- G"
			"G|G";

		color_ = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

		isWalkable_[Top] = true;
		isWalkable_[Bottom] = true;
		isWalkable_[Left] = true;
	}
};
REGISTER_TILE_TYPE(TilePathTopBottomLeft);

// Cross
class TilePathCross : public Tile
{
public:
	TilePathCross()
	{
		stringRepresentation_ =
			"G|G"
			"- -"
			"G|G";

		color_ = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

		isWalkable_[Top] = true;
		isWalkable_[Bottom] = true;
		isWalkable_[Left] = true;
		isWalkable_[Right] = true;
	}
};
REGISTER_TILE_TYPE(TilePathCross);