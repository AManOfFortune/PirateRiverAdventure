#include "scene_camera.h"

#include <glm/gtc/matrix_transform.hpp>

SceneCamera::SceneCamera()
{
	RecalculateProjection();
}

void SceneCamera::SetOrthographic(float size, float near, float far)
{
	orthographic_size_ = size;
	orthographic_near_ = near;	
	orthographic_far_ = far;
	RecalculateProjection();
}

void SceneCamera::RecalculateProjection()
{
	float orthoLeft = -orthographic_size_ * aspect_ratio_ * 0.5f;
	float orthoRight = orthographic_size_ * aspect_ratio_ * 0.5f;
	float orthoBottom = -orthographic_size_ * 0.5f;
	float orthoTop = orthographic_size_ * 0.5f;

	projection_ = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, orthographic_near_, orthographic_far_);
}
