#include "item.h"

void Item::AttachToScene(std::shared_ptr<Scene> scene)
{
    // Create item at position
    entity_ = scene->CreateEntity("Item", GetPosition());

	// Add sprite renderer component with texture
	auto textureAtlas = Texture2D::Create(textureAtlasPath_);
	auto texture = SubTexture2D::CreateFromCoords(textureAtlas, textureCoords_, textureAtlasTileSize_);
	entity_.AddComponent<SpriteRendererComponent>(texture);

    // Set scale
    entity_.GetComponent<TransformComponent>().SetScale(scale_);
}

void Item::DetachFromScene()
{
	// Remove entity from scene
	entity_.Destroy();
}

void Item::SetPosition(glm::vec3 position)
{
	position_ = position;
}

glm::vec3 Item::GetPosition() const
{
	glm::vec3 position = position_;
	position.z += zOffset_;
	return position;
}

bool Item::IsDecorative() const
{
	return isDecorative_;
}

Item::Item()
{
	textureAtlasPath_ = "";
	textureCoords_ = glm::vec2(0.0f);
	textureAtlasTileSize_ = glm::vec2(16, 16);
	position_ = glm::vec3(0.0f);
	scale_ = glm::vec3(0.5f);
    zOffset_ = 0.5f; // Infront of tiles z0, behind player z1
	isDecorative_ = true;
}
