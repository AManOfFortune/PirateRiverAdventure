#pragma once

#include "core/delta_time.h"
#include "core/events/application_event.h"
#include "core/events/mouse_event.h"
#include "renderer/orthographic_camera.h"

class OrthographicCameraController
{
public:
	OrthographicCameraController(float aspectRatio, bool canRotate = false);

	void OnUpdate(DeltaTime deltaTime);
	void OnEvent(Event& event);

	inline OrthographicCamera& camera() { return camera_; }
	inline const OrthographicCamera& camera() const { return camera_; }
private:
	bool OnMouseScrolled(MouseScrolledEvent& event);
	bool OnWindowResized(WindowResizeEvent& event);

	float aspect_ratio_;
	float zoom_level_ = 1.0f;
	OrthographicCamera camera_;

	bool can_rotate_;
	glm::vec3 camera_pos_ = { 0.0f, 0.0f, 0.0f };
	float camera_rot_ = 0.0f;
	float camera_translation_speed_ = 5.0f, camera_rotation_speed_ = 180.0f;
};