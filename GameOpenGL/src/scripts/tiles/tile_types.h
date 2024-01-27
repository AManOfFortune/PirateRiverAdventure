#pragma once

// ------------------ Environment tiles ------------------
// Base tiles
class TileGrass : public Tile
{
public:
	TileGrass()
	{
		stringRepresentation_ = 
			"GGG"
			"G G"
			"GGG";

		SetTexture(0, 5);
	}
};
REGISTER_TILE_TYPE(TileGrass);

class TileWater : public Tile
{
public:
	TileWater()
	{
		stringRepresentation_ =
			"WWW"
			"W W"
			"WWW";

		SetTexture(1, 9);
	}
};
REGISTER_TILE_TYPE(TileWater);

// Straight shore tiles
class TileShoreTop : public Tile
{
public:
	TileShoreTop()
	{
		stringRepresentation_ =
			"GGG"
			"W W"
			"WWW";

		SetTexture(1, 10);
	}
};
REGISTER_TILE_TYPE(TileShoreTop);

class TileShoreBottom : public Tile
{
public:
	TileShoreBottom()
	{
		stringRepresentation_ =
			"WWW"
			"W W"
			"GGG";

		SetTexture(1, 8);
	}
};
REGISTER_TILE_TYPE(TileShoreBottom);

class TileShoreLeft : public Tile
{
public:
	TileShoreLeft()
	{
		stringRepresentation_ =
			"GWW"
			"G W"
			"GWW";

		SetTexture(0, 9);
	}
};
REGISTER_TILE_TYPE(TileShoreLeft);

class TileShoreRight : public Tile
{
public:
	TileShoreRight()
	{
		stringRepresentation_ =
			"WWG"
			"W G"
			"WWG";

		SetTexture(2, 9);
	}
};
REGISTER_TILE_TYPE(TileShoreRight);

// Outer shore corners
class TileShoreTopLeft : public Tile
{
public:
	TileShoreTopLeft()
	{
		stringRepresentation_ =
			"GWW"
			"W W"
			"WWW";

		SetTexture(6, 8);
	}
};
REGISTER_TILE_TYPE(TileShoreTopLeft);

class TileShoreTopRight : public Tile
{
public:
	TileShoreTopRight()
	{
		stringRepresentation_ =
			"WWG"
			"W W"
			"WWW";

		SetTexture(5, 8);
	}
};
REGISTER_TILE_TYPE(TileShoreTopRight);

class TileShoreBottomLeft : public Tile
{
public:
	TileShoreBottomLeft()
	{
		stringRepresentation_ =
			"WWW"
			"W W"
			"GWW";

		SetTexture(6, 9);
	}
};
REGISTER_TILE_TYPE(TileShoreBottomLeft);

class TileShoreBottomRight : public Tile
{
public:
	TileShoreBottomRight()
	{
		stringRepresentation_ =
			"WWW"
			"W W"
			"WWG";

		SetTexture(5, 9);
	}
};
REGISTER_TILE_TYPE(TileShoreBottomRight);

// Inner shore corners
class TileWaterTopLeft : public Tile
{
public:
	TileWaterTopLeft()
	{
		stringRepresentation_ =
			"WGG"
			"G G"
			"GGG";

		SetTexture(2, 8);
	}
};
REGISTER_TILE_TYPE(TileWaterTopLeft);

class TileWaterTopRight : public Tile
{
public:
	TileWaterTopRight()
	{
		stringRepresentation_ =
			"GGW"
			"G G"
			"GGG";

		SetTexture(0, 8);
	}
};
REGISTER_TILE_TYPE(TileWaterTopRight);

class TileWaterBottomLeft : public Tile
{
public:
	TileWaterBottomLeft()
	{
		stringRepresentation_ =
			"GGG"
			"G G"
			"WGG";

		SetTexture(2, 10);
	}
};
REGISTER_TILE_TYPE(TileWaterBottomLeft);

class TileWaterBottomRight : public Tile
{
public:
	TileWaterBottomRight()
	{
		stringRepresentation_ =
			"GGG"
			"G G"
			"GGW";

		SetTexture(0, 10);
	}
};
REGISTER_TILE_TYPE(TileWaterBottomRight);


// ------------------ Path tiles ------------------
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

		isWalkable_[Left] = true;

		SetTexture(2, 7);
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

		isWalkable_[Right] = true;

		SetTexture(0, 7);
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

		isWalkable_[Top] = true;

		SetTexture(3, 8);
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

		isWalkable_[Bottom] = true;

		SetTexture(3, 10);
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

		isWalkable_[Left] = true;
		isWalkable_[Right] = true;

		SetTexture(1, 7);
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

		isWalkable_[Top] = true;
		isWalkable_[Bottom] = true;

		SetTexture(3, 9);
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

		isWalkable_[Top] = true;
		isWalkable_[Right] = true;

		SetTexture(4, 7);
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

		isWalkable_[Top] = true;
		isWalkable_[Left] = true;

		SetTexture(7, 7);
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

		isWalkable_[Bottom] = true;
		isWalkable_[Right] = true;

		SetTexture(4, 10);
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

		isWalkable_[Bottom] = true;
		isWalkable_[Left] = true;

		SetTexture(7, 10);
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


		isWalkable_[Top] = true;
		isWalkable_[Left] = true;
		isWalkable_[Right] = true;

		SetTexture(8, 7);
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


		isWalkable_[Bottom] = true;
		isWalkable_[Left] = true;
		isWalkable_[Right] = true;

		SetTexture(8, 10);
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


		isWalkable_[Top] = true;
		isWalkable_[Bottom] = true;
		isWalkable_[Right] = true;

		SetTexture(4, 6);
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


		isWalkable_[Top] = true;
		isWalkable_[Bottom] = true;
		isWalkable_[Left] = true;

		SetTexture(7, 6);
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


		isWalkable_[Top] = true;
		isWalkable_[Bottom] = true;
		isWalkable_[Left] = true;
		isWalkable_[Right] = true;

		SetTexture(8, 6);
	}
};
REGISTER_TILE_TYPE(TilePathCross);

// Exits
class TileExitBottom : public Tile
{
public:
	TileExitBottom()
	{
		stringRepresentation_ =
			"EEE"
			"E E"
			"E|E";


		isWalkable_[Bottom] = true;
		isExit_ = true;

		SetTexture(8, 9);
	}
};
REGISTER_TILE_TYPE(TileExitBottom);

class TileExitTop : public Tile
{
public:
	TileExitTop()
	{
		stringRepresentation_ =
			"E|E"
			"E E"
			"EEE";

		isWalkable_[Top] = true;
		isExit_ = true;

		SetTexture(8, 8);
	}
};
REGISTER_TILE_TYPE(TileExitTop);

class TileExitLeft : public Tile
{
public:
	TileExitLeft()
	{
		stringRepresentation_ =
			"EEE"
			"- E"
			"EEE";

		isWalkable_[Left] = true;
		isExit_ = true;

		SetTexture(6, 6);
	}
};
REGISTER_TILE_TYPE(TileExitLeft);

class TileExitRight : public Tile
{
public:
	TileExitRight()
	{
		stringRepresentation_ =
			"EEE"
			"E -"
			"EEE";

		isWalkable_[Right] = true;
		isExit_ = true;

		SetTexture(5, 6);
	}
};
REGISTER_TILE_TYPE(TileExitRight);