#pragma once

#include "core/core.h"
#include "example_layer.h"
#include "game_layer.h"

class Game : public Application
{
public:
    Game()
    {
        PushLayer(new GameLayer());
    }
};