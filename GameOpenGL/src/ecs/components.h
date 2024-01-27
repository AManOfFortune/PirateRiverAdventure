#pragma once

#include "scene_camera.h"
#include "scriptable_entity.h"
#include "renderer/texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
	TransformComponent(const glm::vec3& position) : transform(glm::translate(glm::mat4(1.0f), position)) {}

	// Implicit cast operators for convenience when needed to access the underlying mat4.
	operator glm::mat4& () { return transform; }
	operator const glm::mat4& () const { return transform; }

	// Get position
	glm::vec3 GetPosition() const
	{
		return glm::vec3(transform[3]);
	}

	void SetPosition(const glm::vec3& position)
	{
		transform[3] = glm::vec4(position, 1.0f);
	}

    void SetRotation(const glm::vec3& rotation)
    {
        // Create a rotation matrix for the given rotation
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

        // Extract the current scale and position from the transform matrix
        glm::vec3 scale = glm::vec3(glm::length(transform[0]), glm::length(transform[1]), glm::length(transform[2]));
        glm::vec3 position = glm::vec3(transform[3]);

        // Create a new transform matrix with the given rotation, current scale, and position
        transform = glm::translate(glm::mat4(1.0f), position) * rotationMatrix * glm::scale(glm::mat4(1.0f), scale);
    }

	void SetScale(const glm::vec3& scale)
	{
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

		// Multiply the original matrix by the scaling matrix
		transform = transform * scaleMatrix;
	}
};

/// <summary>
/// The sprite renderer component only stores the color of the sprite for now. Needs to be updated for our needs later.
/// </summary>
struct SpriteRendererComponent
{
	std::shared_ptr<SubTexture2D> texture = nullptr;
	Texture2DProperties props;

	SpriteRendererComponent() = default;
	SpriteRendererComponent(const SpriteRendererComponent& spriteRenderer) = default;
	SpriteRendererComponent(const glm::vec4& color) : props(Texture2DProperties(1.0f, color, nullptr)) {}
	SpriteRendererComponent(const std::shared_ptr<SubTexture2D>& texture, const Texture2DProperties& props = Texture2DProperties()) 
		:  texture(texture), props(props) {}

	void SwapTexture(const std::shared_ptr<SubTexture2D>& texture)
	{
		this->texture = texture;
	}
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

struct LightComponent
{
	glm::vec3 color;
	float ambientStrength;

	LightComponent() = default;
	LightComponent(const LightComponent& light) = default;
	LightComponent(const glm::vec3& color, float ambientStrength) : color(color), ambientStrength(ambientStrength) {}
};