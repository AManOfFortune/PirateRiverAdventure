#pragma once

#include <cstdint>

/// <summary>
/// Abstraction layer for the OpenGL vertex buffer class. Technically not needed for our 
/// OpenGL project, however if we wanted to support other rendering APIs (e.g. DirectX) 
/// we could easily extend our rendering logic.
/// </summary>
class VertexBuffer
{
public:
    virtual ~VertexBuffer() {}

    /// <summary>
    /// Factory method to create a vertex buffer regardless of implementation details.
    /// </summary>
    static VertexBuffer* Create(float* vertices, uint32_t size);

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
};

/// <summary>
/// Abstraction layer for the OpenGL index buffer class. Technically not needed for our 
/// OpenGL project, however if we wanted to support other rendering APIs (e.g. DirectX) 
/// we could easily extend our rendering logic.
/// </summary>
class IndexBuffer
{
public:
    virtual ~IndexBuffer() {}

    /// <summary>
    /// Factory method to create an index (element) buffer regardless of implementation details.
    /// </summary>
    static IndexBuffer* Create(uint32_t* indices, uint32_t count);

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual uint32_t count() const = 0;
};