#include "application.h"
#include "log.h"

int main(int argc, char** argv)
{
    Log::Initialize();

    LOG_DEBUG("Initialized logger!");

    auto app = CreateApplication();
    app->Run();
    delete app;
}