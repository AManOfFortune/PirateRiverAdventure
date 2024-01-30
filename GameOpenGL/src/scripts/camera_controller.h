#pragma once

#include "core/input/input.h"
#include "core/input/key_codes.h"
#include "ecs/components.h"
#include "ecs/scriptable_entity.h"

class CameraController : public ScriptableEntity
{
public:
	void OnCreate() {}

	void OnDestroy() {}

	void OnUpdate(DeltaTime ts)
	{
		auto& transform = GetComponent<TransformComponent>().transform;

		if (Input::IsKeyPressed(CG_KEY_LEFT))
			transform[3][0] -= speed_ * ts;
		if (Input::IsKeyPressed(CG_KEY_RIGHT))
			transform[3][0] += speed_ * ts;
		if (Input::IsKeyPressed(CG_KEY_DOWN))
			transform[3][1] -= speed_ * ts;
		if (Input::IsKeyPressed(CG_KEY_UP))
			transform[3][1] += speed_ * ts;
	}

private:
	float speed_ = 5.0f;
};