#pragma once

#include <glm/glm.hpp>

struct LightProperties
{
	LightProperties()
		: position(glm::vec3(0.0f)), color(glm::vec3(1.0f)), ambientStrength(0.1f)
	{}

	LightProperties(const glm::vec3& position, const glm::vec3& color, float ambientStrength)
		: position(position), color(color), ambientStrength(ambientStrength)
	{}

	glm::vec3 position;
	glm::vec3 color;
	float ambientStrength = 0.1f;
};