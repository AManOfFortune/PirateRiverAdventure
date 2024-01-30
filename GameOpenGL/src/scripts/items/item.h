#pragma once
#include "ecs/scene.h"
#include "ecs/components.h"

class Item
{
public:
	virtual void AttachToScene(std::shared_ptr<Scene> scene);
	void DetachFromScene();

	void SetPosition(glm::vec3 position);
	glm::vec3 GetPosition() const;

	bool IsDecorative() const;

protected:
	Item();

	glm::vec3 position_;
	glm::vec3 scale_;
	std::string textureAtlasPath_;
	glm::vec2 textureAtlasTileSize_;
	glm::vec2 textureCoords_;

	Entity entity_;

	float zOffset_;

	bool isDecorative_;
};
