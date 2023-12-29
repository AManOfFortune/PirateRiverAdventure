#include "orthographic_camera_controller.h"

#include "core/input/input.h"
#include "core/input/key_codes.h"

OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool canRotate)
    : aspect_ratio_{ aspectRatio }, camera_(-aspectRatio * zoom_level_, aspectRatio * zoom_level_, -zoom_level_, zoom_level_), can_rotate_{ canRotate }
{ }

void OrthographicCameraController::OnUpdate(DeltaTime deltaTime)
{
    // Camera movement
    if (Input::IsKeyPressed(CG_KEY_A))
    {
        camera_pos_.x -= cos(glm::radians(camera_rot_)) * camera_translation_speed_ * deltaTime;
        camera_pos_.y -= sin(glm::radians(camera_rot_)) * camera_translation_speed_ * deltaTime;
    }
    else if (Input::IsKeyPressed(CG_KEY_D))
    {
        camera_pos_.x += cos(glm::radians(camera_rot_)) * camera_translation_speed_ * deltaTime;
        camera_pos_.y += sin(glm::radians(camera_rot_)) * camera_translation_speed_ * deltaTime;
    }

    if (Input::IsKeyPressed(CG_KEY_S))
    {
        camera_pos_.x -= -sin(glm::radians(camera_rot_)) * camera_translation_speed_ * deltaTime;
        camera_pos_.y -= cos(glm::radians(camera_rot_)) * camera_translation_speed_ * deltaTime;
    }
    else if (Input::IsKeyPressed(CG_KEY_W))
    {
        camera_pos_.x += -sin(glm::radians(camera_rot_)) * camera_translation_speed_ * deltaTime;
        camera_pos_.y += cos(glm::radians(camera_rot_)) * camera_translation_speed_ * deltaTime;
    }

    // Camera rotation if enabled
    if (can_rotate_)
    {
        if (Input::IsKeyPressed(CG_KEY_Q))
            camera_rot_ += camera_rotation_speed_ * deltaTime;
        else if (Input::IsKeyPressed(CG_KEY_E))
            camera_rot_ -= camera_rotation_speed_ * deltaTime;

        if (camera_rot_ > 180.0f)
			camera_rot_ -= 360.0f;
		else if (camera_rot_ <= -180.0f)
			camera_rot_ += 360.0f;

        camera_.set_rotation(camera_rot_);
    }

    camera_.set_position(camera_pos_);
    // The camera translation speed is dependent on the zoom level.
    camera_translation_speed_ = zoom_level_;
}

void OrthographicCameraController::OnEvent(Event& event)
{
    // Bind MouseScrolledEvent, WindowResizeEvent and KeyPressedEvent to their respective methods.
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&OrthographicCameraController::OnMouseScrolled, this, std::placeholders::_1));
	dispatcher.Dispatch<WindowResizeEvent>(std::bind(&OrthographicCameraController::OnWindowResized, this, std::placeholders::_1));
}

bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event)
{
    // Zoom in or out depending on the mouse scroll direction.
	zoom_level_ -= event.y_offset() * 0.25f;
	zoom_level_ = std::max(zoom_level_, 0.25f);
    // Update projection matrix.
    camera_.set_projection_matrix(-aspect_ratio_ * zoom_level_, aspect_ratio_* zoom_level_, -zoom_level_, zoom_level_);
	return false;
}

bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& event)
{
    // Update the aspect ratio and the projection matrix.
    aspect_ratio_ = (float)event.width() / (float)event.height();
    camera_.set_projection_matrix(-aspect_ratio_ * zoom_level_, aspect_ratio_ * zoom_level_, -zoom_level_, zoom_level_);
	return false;
}
