#include "sandbox.h"
#include "game.h"

int main(int argc, char** argv)
{
    Log::Initialize();
    LOG_DEBUG("Initialized logger!");

    auto app = new Game;
    //auto app = new Sandbox;
    app->Run();
    delete app;
}
