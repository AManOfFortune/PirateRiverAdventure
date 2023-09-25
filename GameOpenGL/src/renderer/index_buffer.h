#pragma once

#include <cstdint>

/// <summary>
/// An OpenGL index (element) buffer class.
/// </summary>
class IndexBuffer
{
public:
    IndexBuffer(uint32_t* indices, uint32_t count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    uint32_t count() const { return count_; }

private:
    uint32_t renderer_id_;
    uint32_t count_;
};