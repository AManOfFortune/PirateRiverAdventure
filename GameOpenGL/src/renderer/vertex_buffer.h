#pragma once

#include "vertex_buffer_layout.h"

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

    inline const VertexBufferLayout& layout() const { return layout_; }
    inline void set_layout(const VertexBufferLayout& layout) { layout_ = layout; }

private:
    uint32_t renderer_id_;
    VertexBufferLayout layout_;
};