#pragma once

#include <memory>

struct GLFWwindow;

/// <summary>
/// A class that represents the OpenGL context.
/// </summary>
class Context
{
public:
    Context(GLFWwindow* window);

    static std::unique_ptr<Context> Create(GLFWwindow* window);

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