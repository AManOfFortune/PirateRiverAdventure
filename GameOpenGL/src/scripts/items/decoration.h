#pragma once
#include "item.h"

class Decoration : public Item
{
protected:
	Decoration() {
		isDecorative_ = true;
		zOffset_ = 0.0f;
	}
};