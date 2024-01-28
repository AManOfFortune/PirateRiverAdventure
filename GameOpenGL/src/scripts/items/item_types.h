#pragma once
#include "item.h"

class Key : public Item
{
public:
	Key() {
		textureAtlasPath_ = "assets/textures/NinjaAdventure/Items/Treasure/Coin2.png";
		textureAtlasTileSize_ = glm::vec2(10, 10);
		textureCoords_ = glm::vec2(1, 0);
		isDecorative_ = false;
	}
};

class Exit : public Item
{
public: 
	Exit() {
		textureAtlasPath_ = "assets/textures/NinjaAdventure/Backgrounds/Tilesets/TilesetLogic.png";
		textureAtlasTileSize_ = glm::vec2(16, 16);
		textureCoords_ = glm::vec2(4, 4);
		zOffset_ = 0.0f;
	}
};