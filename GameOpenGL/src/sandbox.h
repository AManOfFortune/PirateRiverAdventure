#pragma once

#include "core/core.h"
#include "example_layer.h"
#include "sandbox_2d_layer.h"

class Sandbox : public Application
{
public:
    Sandbox()
    {
        PushLayer(new Sandbox2DLayer());
    }
};