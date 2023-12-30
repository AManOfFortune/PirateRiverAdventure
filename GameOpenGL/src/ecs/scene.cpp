#include "scene.h"

#include <glm/glm.hpp>

static void OnTransformConstruct(entt::registry& registry, entt::entity entity)
{

}

Scene::Scene()
{
	// Here we create an entity, internally it is simply an uint32_t.
	// Because it is just an integer, it does not contain any methods or data.
	// Any time we want to modify an entity, we need to use the registry.
	entt::entity entity = registry_.create();

	// The components are just structs because we do not need any inheritance.
	struct TransformComponent
	{
		glm::mat4 transform;

		TransformComponent() = default;
		TransformComponent(const TransformComponent& transform) = default;
		TransformComponent(const glm::mat4& transform) : transform(transform) {}

		// Implicit cast operators for convenience when needed to access the underlying mat4.
		operator glm::mat4& () { return transform; }
		operator const glm::mat4& () const { return transform; }
	};

	// This is how components are added to an entity. 
	// Fist we need to specify the entity we want to add the component to, then the component arguments.
	registry_.emplace<TransformComponent>(entity, glm::mat4(1.0f));

	// Checking if a component exists and then getting it looks like this.
	if (registry_.all_of<TransformComponent>(entity))
		TransformComponent& transform = registry_.get<TransformComponent>(entity);

	// Iterating over all entities that have a TransformComponent looks like this.
	// First we need to get a view of all entities that have the component.
	// Then we can iterate over the view and get the entity from it.
	// A use case for this would be to render all sprite/mesh components.
	auto view = registry_.view<TransformComponent>();
	for (auto entity : view)
	{
		TransformComponent& transform = view.get<TransformComponent>(entity);
	}

	// Here we connect a function to be called when a transform component is constructed.
	registry_.on_construct<TransformComponent>().connect<&OnTransformConstruct>(entity);

}

Scene::~Scene()
{
}
