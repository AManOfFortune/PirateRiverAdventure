#pragma once

#include <glm/glm.hpp>

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

struct SpriteRendererComponent
{
	glm::vec4 color{ 1.0f, 1.0f, 1.0f, 1.0f };

	SpriteRendererComponent() = default;
	SpriteRendererComponent(const SpriteRendererComponent& spriteRenderer) = default;
	SpriteRendererComponent(const glm::vec4& color) : color(color) {}
};

