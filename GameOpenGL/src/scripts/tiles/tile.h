#pragma once
#include "core/core.h"

class Tile
{
public:
	glm::vec3 getPosition() { return position_; };
	void setPosition(glm::vec3 position) { position_ = position; };

	glm::vec4 getColor() { return color_; };
	const std::string& getRepresentation() const { return stringRepresentation_; };

protected:
	Tile() {
		size_ = glm::vec3(1.0f, 1.0f, 1.0f);
		position_ = glm::vec3(0.0f);
		color_ = glm::vec4(1.0f);
	};

	std::string stringRepresentation_;
	glm::vec3 position_;
	glm::vec3 size_;
	glm::vec4 color_;
};

