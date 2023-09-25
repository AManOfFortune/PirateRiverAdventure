#pragma once

#include <cstdint>

/// <summary>
/// An OpenGL vertex buffer class.
/// </summary>
class VertexBuffer
{
public:
    VertexBuffer(float* vertices, uint32_t size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

private:
    uint32_t renderer_id_;
};