#include "input.h"

#include "application/application.h"

#include <GLFW/glfw3.h>

Input* Input::instance_ = new Input();

bool Input::IsKeyPressed(int key)
{
    GLFWwindow* window = Application::Instance().window().glfw_window();
    int state = glfwGetKey(window, key);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsMouseButtonPressed(int button)
{
    GLFWwindow* window = Application::Instance().window().glfw_window();
    int state = glfwGetMouseButton(window, button);
    return state == GLFW_PRESS;
}

std::pair<float, float> Input::MousePosition()
{
    GLFWwindow* window = Application::Instance().window().glfw_window();
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    return std::make_pair((float)xPos, (float)yPos);
}

float Input::MouseX()
{
    std::pair<float, float> pos = MousePosition();
    return std::get<0>(pos);
}

float Input::MouseY()
{
    std::pair<float, float> pos = MousePosition();
    return std::get<1>(pos);
}