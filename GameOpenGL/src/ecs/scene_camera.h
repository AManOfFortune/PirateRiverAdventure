#pragma once

#include "renderer/camera.h"

class SceneCamera : public Camera
{
public:
	SceneCamera();
	virtual ~SceneCamera() = default;

	void SetOrthographic(float size, float near, float far);

	float orthographic_size() const { return orthographic_size_; }
	void set_orthographic_size(float size) { orthographic_size_ = size; RecalculateProjection(); }

	float aspect_ratio() const { return aspect_ratio_; }
	void set_aspect_ratio(float aspect_ratio) { aspect_ratio_ = aspect_ratio; RecalculateProjection(); }

private:
	void RecalculateProjection();

	float orthographic_size_ = 10.0f;
	float orthographic_near_ = -1.0f, orthographic_far_ = 1.0f;
	float aspect_ratio_ = 16.0f / 9.0f;
};