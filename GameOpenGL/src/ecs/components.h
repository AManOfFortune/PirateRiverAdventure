#pragma once

#include "scene_camera.h"

#include <glm/glm.hpp>

/// <summary>
/// The TagComponent is used to identify an entity with a string tag.
/// </summary>
struct TagComponent
{
	std::string tag;

	TagComponent() = default;
	TagComponent(const TagComponent& tag) = default;
	TagComponent(const std::string& tag) : tag(tag) {}
};

/// <summary>
/// The transform component is used to store the position, rotation and scale of an entity.
/// </summary>
struct TransformComponent
{
	glm::mat4 transform{ 1.0f };

	TransformComponent() = default;
	TransformComponent(const TransformComponent& transform) = default;
	TransformComponent(const glm::mat4& transform) : transform(transform) {}

	// Implicit cast operators for convenience when needed to access the underlying mat4.
	operator glm::mat4& () { return transform; }
	operator const glm::mat4& () const { return transform; }
};

/// <summary>
/// The sprite renderer component only stores the color of the sprite for now. Needs to be updated for our needs later.
/// </summary>
struct SpriteRendererComponent
{
	// For now, we only support a single color for the entire sprite.
	// TODO: Add textures, normal maps, ... later.
	glm::vec4 color{ 1.0f, 1.0f, 1.0f, 1.0f };

	SpriteRendererComponent() = default;
	SpriteRendererComponent(const SpriteRendererComponent& spriteRenderer) = default;
	SpriteRendererComponent(const glm::vec4& color) : color(color) {}
};

struct CameraComponent
{
	SceneCamera camera;
	bool isPrimary = true;
	bool isFixedAspectRatio = false;

	CameraComponent() = default;
	CameraComponent(const CameraComponent& camera) = default;
};