#pragma once

struct GLFWwindow;

/// <summary>
/// A class that holds the OpenGL context. While not necessary for our purpose a general
/// context class could be created that is inherited by different subclasses (e.g. DirectXContext)
/// in order to abstract the GLFW window should we decide to replace it later. 
/// </summary>
class OpenGLContext
{
public:
    OpenGLContext(GLFWwindow* window);

    /// <summary>
    /// Initializes the context and glad.
    /// </summary>
    void Initialize();
    /// <summary>
    /// Swaps the front and back buffers of the window.
    /// </summary>
    void SwapBuffers();

private:
    GLFWwindow* window_;
};