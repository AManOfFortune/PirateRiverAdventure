#pragma once

#include <glm/glm.hpp>

class OrthographicCamera
{
public:
    OrthographicCamera(float left, float right, float bottom, float top);

    const glm::mat4& projection_matrix() const { return projection_matrix_; }
    void set_projection_matrix(float left, float right, float bottom, float top);

    const glm::mat4& view_matrix() const { return view_matrix_; }
    const glm::mat4& projection_view_matrix() const { return projection_view_matrix_; }

    const glm::vec3& position() const { return position_; }
    void set_position(const glm::vec3& position) { position_ = position; RecalculateViewMatrix(); }

    float rotation() const { return rotation_; }
    void set_rotation(float rotation) { rotation_ = rotation; RecalculateViewMatrix(); }

private:
    void RecalculateViewMatrix();

    glm::mat4 projection_matrix_ = glm::mat4(1.0f);
    glm::mat4 view_matrix_ = glm::mat4(1.0f);
    glm::mat4 projection_view_matrix_ = glm::mat4(1.0f);

    glm::vec3 position_ = { 0.0f, 0.0f, 0.0f };
    // The camera rotation in degrees.
    float rotation_ = 0.0f;
};
