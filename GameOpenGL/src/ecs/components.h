#pragma once

#include "scene_camera.h"
#include "scriptable_entity.h"

#include <glm/glm.hpp>
#include <string>

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

/// <summary>
/// The camera component stores the camera used to render the scene.
/// </summary>
struct CameraComponent
{
	SceneCamera camera;
	bool isPrimary = true;
	bool isFixedAspectRatio = false;

	CameraComponent() = default;
	CameraComponent(const CameraComponent& camera) = default;
};


struct ScriptComponent
{
	ScriptableEntity* instance = nullptr;

	/// <summary>
	/// Function pointer to the function that instantiates the scriptable entity.
	/// The target function has the signature: ScriptableEntity* foo();
	/// </summary>
	ScriptableEntity* (*instantiateScript)() = nullptr;
	/// <summary>
	/// Function pointer to the function that destroys the script component.
	/// The target function has the signature: void foo(ScriptComponent*);
	/// </summary>
	void (*destroyScript)(ScriptComponent*) = nullptr;

	/// <summary>
	/// Binds the script component to the given scriptable entity class.
	/// </summary>
	template<typename T>
	void Bind()
	{
		// Binds the instantiateScript function pointer to a function that allocates a new instance of 
		// the given template type T which is then cast to a ScriptableEntity*.
		instantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };

		// Binds the destroyScript function pointer to a function that deletes the given script component.
		destroyScript = [](ScriptComponent* scriptComponent) 
		{
			delete scriptComponent->instance;
			scriptComponent->instance = nullptr;
		};
	}
};