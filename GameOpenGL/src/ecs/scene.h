#pragma once

#include "core/delta_time.h"
#include <glm/glm.hpp>

#include <entt.hpp>

// Forward declaration of Entity class. We need this because we have a circular dependency.
class Entity;

/// <summary>
/// A scene is a container for all entities and their components and provides an API to create entities.
/// For now, the entities created here always have a tag and a transform component.
/// </summary>
class Scene
{
public:
	Scene();
	~Scene();

	void OnUpdate(DeltaTime deltaTime);
	void OnResize(uint32_t width, uint32_t height);

	/// <summary>
	/// Creates an entity with the given name as tag. They are not unique yet, so multiple entities can have the same name.
	/// For now, each entity is automatically given a tag and a transform component.
	/// </summary>
	//Entity CreateEntity(const std::string& name = std::string());

	/// <summary>
	/// Creates an entity with the given name as tag and the given position.
	/// </summary>
	Entity CreateEntity(const std::string& name = std::string(), glm::vec3 position = glm::vec3(0.0f));

private:
	// An entity is basically just an ID that is associated with a bunch of components.
	// The registry holds the actual data for the components as well as the entity IDs.
	// It can be seen as the container for all entities. Here, we choose to create a 
	// registry for each scene. There are possibilities to persist registries across scenes,
	// but we won't do that here.
	entt::registry registry_;
	// Defined as friend so that it can access the underlying registry_.
	friend class Entity;
};

