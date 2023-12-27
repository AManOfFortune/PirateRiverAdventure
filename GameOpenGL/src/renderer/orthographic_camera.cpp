#include "orthographic_camera.h"

#include <glm/gtc/matrix_transform.hpp>

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    : projection_matrix_(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
{
    projection_view_matrix_ = projection_matrix_ * view_matrix_;
}

void OrthographicCamera::set_projection_matrix(float left, float right, float bottom, float top)
{
    projection_matrix_ = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    projection_view_matrix_ = projection_matrix_ * view_matrix_;
}

void OrthographicCamera::RecalculateViewMatrix()
{
    // Calculate the inverse view matrix by translating first and rotating afterwards.
    glm::mat4 almostViewMatrix = glm::translate(glm::mat4(1.0f), position_) * 
        glm::rotate(glm::mat4(1.0f), glm::radians(rotation_), glm::vec3(0.0f, 0.0f, 1.0f));

    // Inverse the matrix to create the view matrix. This is because any "camera" movement should
    // actually move all scene elements in the opposite direction.
    view_matrix_ = glm::inverse(almostViewMatrix);

    // Update the projection view matrix (P * V).
    projection_view_matrix_ = projection_matrix_ * view_matrix_;
}
