#pragma once

#include "core/utils.h"

#include <entt.hpp>
#include <memory>

#include "scene.h"
/// <summary>
/// This is a wrapper over entt::entity (which is just an uint32_t) which stores the ID and the scene it belongs to.
/// </summary>
class Entity
{
public:
	Entity() = default;
	Entity(entt::entity entity, Scene* scene);
	Entity(const Entity& other) = default;

	// This variadic template forwards the constructor arguments to the entt::registry::emplace method.
	// This method works for any number of arguments.
	template<typename T, typename... Args>
	T& AddComponent(Args&&... args) // The && means that the arguments are rvalue references, which means that they can be moved.
	{
		ASSERT(!HasComponent<T>(), "Entity already has component!");

		// Do not unpack the arguments here, because we want to forward them to the emplace method.
		return scene_->registry_.emplace<T>(entity_, std::forward<Args>(args)...); // The forward method is used to forward the rvalue references as lvalue references.
	}

	template<typename T>
	T& GetComponent()
	{
		ASSERT(HasComponent<T>(), "Entity does not have component!");

		return scene_->registry_.get<T>(entity_);
	}

	template<typename T>
	bool HasComponent()
	{
		return scene_->registry_.all_of<T>(entity_);
	}

	template<typename T>
	void RemoveComponent()
	{
		ASSERT(HasComponent<T>(), "Entity does not have component!");

		scene_->registry_.remove<T>(entity_);
	}

	operator bool() const { return entity_ != entt::null; }

private:
	entt::entity entity_{ entt::null };
	// We do not want to delete this should the entity be destroyed since the scene should still live on.
	Scene* scene_ = nullptr;
};