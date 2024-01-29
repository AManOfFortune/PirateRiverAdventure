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

class FishingRod : public Item
{
public:
FishingRod() {
		textureAtlasPath_ = "assets/textures/NinjaAdventure/Items/Weapons/FishingRod/Sprite.png";
		textureAtlasTileSize_ = glm::vec2(10, 14);
		textureCoords_ = glm::vec2(0, 0);
	}
};