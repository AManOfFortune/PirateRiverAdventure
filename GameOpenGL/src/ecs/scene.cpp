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
	// Here, all script components are created/updated.
	{
		registry_.view<ScriptComponent>().each([=](auto entity, auto& scriptComponent)
		{
			// Instantiate the script instance if it doesn't exist yet then call its OnCreate method.
			if (!scriptComponent.instance)
			{
				scriptComponent.instance = scriptComponent.instantiateScript();
				scriptComponent.instance->entity_ = Entity(entity, this);
				scriptComponent.instance->OnCreate();
			}

			// Call the OnUpdate method of the script instance.
			scriptComponent.instance->OnUpdate(deltaTime);
		});
	}


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
			if (spriteRenderer.texture != nullptr)
			{
				Renderer2D::DrawQuad(transform.transform, spriteRenderer.texture, spriteRenderer.props);
			}
			else
			{
				Renderer2D::DrawQuad(transform.transform, spriteRenderer.props.tintColor);
			}
		}

		Renderer2D::EndScene();
	}	
}

void Scene::OnResize(uint32_t width, uint32_t height)
{
	auto view = registry_.view<CameraComponent>();
	for (auto entity : view)
	{
		CameraComponent& cameraComponent = view.get<CameraComponent>(entity);

		if (!cameraComponent.isFixedAspectRatio)
			cameraComponent.camera.set_aspect_ratio((float)width / (float) height);
	}
}

void Scene::ClearScene()
{
	registry_.clear();
}

Entity Scene::CreateEntity(const std::string& name, glm::vec3 position)
{
	Entity entity = Entity(registry_.create(), this);

	// Here, all entities are created with a tag and transform component.
	TagComponent& tag = entity.AddComponent<TagComponent>();
	tag.tag = name.empty() ? "Entity" : name;
	entity.AddComponent<TransformComponent>(position);

	return entity;
}

