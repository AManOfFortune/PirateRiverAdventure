#pragma once

/// <summary>
/// Specifies the used rendering API.
/// </summary>
enum class RendererAPI
{
    kNone = 0, kOpenGL = 1
};

/// <summary>
/// Abstraction layer for the rendering API. Technically not needed for our OpenGL project,
/// however if we wanted to support other rendering APIs (e.g. DirectX) we could easily
/// extend our rendering logic.
/// </summary>
class Renderer
{
public:
    inline static RendererAPI API() { return rendererAPI; }

private:
    static RendererAPI rendererAPI;
};