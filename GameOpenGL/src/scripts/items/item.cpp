#include "item.h"

void Item::AttachToScene(std::shared_ptr<Scene> scene)
{
    // Create item at position
    entity_ = scene->CreateEntity("Item", GetPosition());
    // Add sprite renderer component
    entity_.AddComponent<SpriteRendererComponent>(color_);
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

Item::Item()
{
	position_ = glm::vec3(0.0f);
	color_ = glm::vec4(1.0f);
	scale_ = glm::vec3(0.5f);
    zOffset_ = 0.5f; // Infront of tiles z0, behind player z1
}
