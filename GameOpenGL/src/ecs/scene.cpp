#include "scene.h"

#include "components.h"
#include "entity.h"
#include "renderer/renderer.h"
#include "renderer/renderer_2d.h"

#include <glm/glm.hpp>
#include <memory>

Scene::Scene()
{

}

Scene::~Scene()
{
}

void Scene::OnUpdate(DeltaTime deltaTime)
{
	Camera* mainCamera = nullptr;
	glm::mat4* transform = nullptr;
	{
		auto view = registry_.view<TransformComponent, CameraComponent>();
		for (auto entity : view)
		{
			auto [transformComponent, cameraComponent] = view.get<TransformComponent, CameraComponent>(entity);

			if (cameraComponent.isPrimary)
			{
				mainCamera = &cameraComponent.camera;
				transform = &transformComponent.transform;
				break;
			}
		}
	}

	if (mainCamera)
	{
		Renderer2D::BeginScene(*mainCamera, *transform);

		// Here, we get all entities that have a transform and sprite renderer component and issue a draw call for them.
		auto group = registry_.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto [transform, spriteRenderer] = group.get<TransformComponent, SpriteRendererComponent>(entity);
			Renderer2D::DrawQuad(transform.transform, spriteRenderer.color);
		}

		Renderer2D::EndScene();
	}
}

/// <summary>
/// Creates an entity with a tag and transform component.
/// </summary>
Entity Scene::CreateEntity(const std::string& name)
{
	Entity entity = Entity(registry_.create(), this);

	// Here, all entities are created with a tag and transform component.
	TagComponent& tag = entity.AddComponent<TagComponent>();
	tag.tag = name.empty() ? "Entity" : name;
	entity.AddComponent<TransformComponent>();

	return entity;
}
