#pragma once
#include "item.h"

class Key : public Item
{
public:
	Key() {
		color_ = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
	}
};