#pragma once

#include <entt.hpp>

class Scene
{
public:
	Scene();
	~Scene();

private:
	// An entity is basically just an ID that is associated with a bunch of components.
	// The registry holds the actual data for the components as well as the entity IDs.
	// It can be seen as the container for all entities. Here, we choose to create a 
	// registry for each scene. There are possibilities to persist registries across scenes,
	// but we won't do that here.
	entt::registry registry_;
};

