#pragma once

#include "entity.h"

/// <summary>
/// Extends the Entity class to allow for scripting.
/// It is the equivalent of a MonoBehaviour in Unity.
/// </summary>
class ScriptableEntity : Entity
{
public:
	template<typename T>
	T& GetComponent()
	{
		return entity_.GetComponent<T>();
	}
protected:
	virtual void OnCreate() {}
	virtual void OnDestroy() {}
	virtual void OnUpdate(DeltaTime deltaTime) {}

private:
	Entity entity_;
	// Allow the Scene class to access the private members of this class.
	friend class Scene;
};