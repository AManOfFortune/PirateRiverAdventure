#pragma once

#include "core/input/input.h"
#include "core/input/key_codes.h"
#include "ecs/components.h"
#include "ecs/scriptable_entity.h"
#include "tiles/tile.h"

class Player : public ScriptableEntity
{
public:
	void OnCreate();

	void OnDestroy();

	void OnUpdate(DeltaTime ts);

private:
	float moveSpeedInSeconds_ = 1.0f;
	float currentTime_ = 0.0f;

	glm::vec3 MoveOverTime(const glm::vec3& startPos, const glm::vec3& endPos, float durationInSeconds, float& currentTime, float deltaTime);
};