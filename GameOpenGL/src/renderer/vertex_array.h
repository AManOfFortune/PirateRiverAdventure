#pragma once

#include "index_buffer.h"
#include "vertex_buffer.h"

#include <memory>
#include <vector>


/// <summary>
/// An OpenGL vertex array class.
/// </summary>
class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    static std::shared_ptr<VertexArray> Create();

    void Bind() const;
    void Unbind() const;

    inline const std::vector<std::shared_ptr<VertexBuffer>>& vertex_buffers() const { return vertex_buffers_; }
    void add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);

    inline const std::shared_ptr<IndexBuffer>& index_buffer() const { return index_buffer_; }
    void set_index_buffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

private:
    uint32_t renderer_id_;

    // The vertex array can hold multiple vertex buffers and a single index buffer.
    std::vector<std::shared_ptr<VertexBuffer>> vertex_buffers_;
    std::shared_ptr<IndexBuffer> index_buffer_;
};