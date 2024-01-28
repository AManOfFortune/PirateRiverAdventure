#pragma once
#include "decoration.h"

class Exit : public Decoration
{
public:
	Exit() {
		textureAtlasPath_ = "assets/textures/NinjaAdventure/Backgrounds/Tilesets/TilesetLogic.png";
		textureAtlasTileSize_ = glm::vec2(16, 16);
		textureCoords_ = glm::vec2(4, 4);
	}
};

class BrickWall : public Decoration
{
public:
	enum class WallType {
		StraightFacingUp,
		StraightFacingRight,
		StraightFacingDown,
		StraightFacingLeft,
		CornerTopLeft,
		CornerTopRight,
		CornerBottomRight,
		CornerBottomLeft,
		EndFacingUp,
		EndFacingDown
	};

	BrickWall(WallType wallType) {
		textureAtlasPath_ = "assets/textures/brick_tiles.png";
		normalTexturePath_ = "assets/textures/brick_normals.png";
		textureAtlasTileSize_ = glm::vec2(16, 16);
		scale_ = { 1.0, 1,0 };
		switch (wallType) {
		case WallType::StraightFacingUp:
			textureCoords_ = glm::vec2(3, 1);
			break;
		case WallType::StraightFacingDown:
			textureCoords_ = glm::vec2(3, 0);
			break;
		case WallType::StraightFacingRight:
		case WallType::StraightFacingLeft:
			textureCoords_ = glm::vec2(1, 1);
			break;
		case WallType::CornerTopLeft:
			textureCoords_ = glm::vec2(2, 1);
			break;
		case WallType::CornerTopRight:
			textureCoords_ = glm::vec2(4, 1);
			break;
		case WallType::CornerBottomRight:
			textureCoords_ = glm::vec2(4, 0);
			break;
		case WallType::CornerBottomLeft:
			textureCoords_ = glm::vec2(2, 0);
			break;
		case WallType::EndFacingUp:
			textureCoords_ = glm::vec2(0, 1);
			break;
		case WallType::EndFacingDown:
			textureCoords_ = glm::vec2(0, 0);
			break;
		}
	}

	// Override attach to scene function to add normal map
	void AttachToScene(std::shared_ptr<Scene> scene) override {
		// Create item at position
		entity_ = scene->CreateEntity("BrickWall", GetPosition());

		// Add sprite renderer component with texture
		auto textureAtlas = Texture2D::Create(textureAtlasPath_);
		auto texture = SubTexture2D::CreateFromCoords(textureAtlas, textureCoords_, textureAtlasTileSize_);
		// Add normal map
		auto normalTextureAtlas = Texture2D::Create(normalTexturePath_);
		auto normalTexture = SubTexture2D::CreateFromCoords(normalTextureAtlas, textureCoords_, textureAtlasTileSize_);
		auto props = Texture2DProperties(normalTexture);

		entity_.AddComponent<SpriteRendererComponent>(texture, props);

		// Set scale
		entity_.GetComponent<TransformComponent>().SetScale(scale_);
	}

private:
	std::string normalTexturePath_;
};