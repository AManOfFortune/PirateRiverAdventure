#pragma once

struct GLFWwindow;

class OpenGLContext
{
public:
    OpenGLContext(GLFWwindow* window);

    void Initialize();
    void SwapBuffers();

private:
    GLFWwindow* window_;
};