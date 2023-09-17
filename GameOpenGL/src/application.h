#pragma once

#include "window.h"

#include <memory>

class Application
{
public:
    Application();
    virtual ~Application();

    void Run();

private:
    std::unique_ptr<Window> window_;
    bool is_running_ = true;
};

Application* CreateApplication();