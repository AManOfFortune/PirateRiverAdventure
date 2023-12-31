#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera(const glm::mat4& projection) 
		: projection_(projection) 
	{}

	inline const glm::mat4& projection() const { return projection_; }

private:
	glm::mat4 projection_;
};