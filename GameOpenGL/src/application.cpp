#include "application.h"

#include <GLFW/glfw3.h>

Application::Application()
{
    window_ = std::unique_ptr<Window>(Window::Create());
}

Application::~Application()
{

}

void Application::Run()
{
    while (is_running_)
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        window_->OnUpdate();
    }
}

Application* CreateApplication()
{
    return new Application();
}