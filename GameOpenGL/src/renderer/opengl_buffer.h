#pragma once

#include "buffer.h"

/// <summary>
/// OpenGL implementation of the abstract vertex buffer class.
/// </summary>
class OpenGLVertexBuffer : public VertexBuffer
{
public:
    OpenGLVertexBuffer(float* vertices, uint32_t size);
    ~OpenGLVertexBuffer();

    void Bind() const;
    void Unbind() const;

private:
    uint32_t renderer_id_;
};

/// <summary>
/// OpenGL implementation of the abstract index buffer class.
/// </summary>
class OpenGLIndexBuffer : public IndexBuffer
{
public:
    OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
    ~OpenGLIndexBuffer();

    void Bind() const;
    void Unbind() const;

    uint32_t count() const { return count_; }

private:
    uint32_t renderer_id_;
    uint32_t count_;
};