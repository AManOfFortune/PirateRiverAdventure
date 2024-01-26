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

	// TODO: If wanted, we could split the color into diffuse, specular and ambient light colors.
	glm::vec3 position;
	glm::vec3 color;
	float ambientStrength = 0.1f;
};