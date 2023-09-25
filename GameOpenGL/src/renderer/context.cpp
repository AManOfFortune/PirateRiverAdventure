#include "context.h"
#include "core.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Context::Context(GLFWwindow* window)
    : window_(window)
{
    ASSERT(window, "GLFW window is null!");
}

void Context::Initialize()
{
    glfwMakeContextCurrent(window_);
    int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    ASSERT(success, "GLAD could not be initialized!");
    LOG_DEBUG("Loading GLAD: {0}", success);
}

void Context::SwapBuffers()
{
    glfwSwapBuffers(window_);
}
