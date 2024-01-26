#include "entity.h"

Entity::Entity(entt::entity entity, Scene* scene)
	: entity_(entity), scene_(scene)
{ }

void Entity::Destroy()
{
	scene_->registry_.destroy(entity_);
}
