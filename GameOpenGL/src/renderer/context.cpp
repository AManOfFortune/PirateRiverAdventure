#include "context.h"
#include "core/utils.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


Context::Context(GLFWwindow* window)
    : window_(window)
{
    ASSERT(window, "GLFW window is null!");
}

std::unique_ptr<Context> Context::Create(GLFWwindow* window)
{
    return std::make_unique<Context>(window);
}

void Context::Initialize()
{
    glfwMakeContextCurrent(window_);
    int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    ASSERT(success, "GLAD could not be initialized!");
}

void Context::SwapBuffers()
{
    glfwSwapBuffers(window_);
}
