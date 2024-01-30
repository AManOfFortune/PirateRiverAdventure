#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera() = default;
	Camera(const glm::mat4& projection) 
		: projection_(projection) 
	{}
	virtual ~Camera() = default;

	inline const glm::mat4& projection() const { return projection_; }

protected:
	glm::mat4 projection_ = glm::mat4(1.0f);
};
