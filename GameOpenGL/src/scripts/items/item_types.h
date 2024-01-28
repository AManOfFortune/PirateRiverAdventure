#pragma once
#include "item.h"
#include "decoration.h"

class Key : public Item
{
public:
	Key() {
		textureAtlasPath_ = "assets/textures/NinjaAdventure/Items/Treasure/Coin2.png";
		textureAtlasTileSize_ = glm::vec2(10, 10);
		textureCoords_ = glm::vec2(1, 0);
	}
};
