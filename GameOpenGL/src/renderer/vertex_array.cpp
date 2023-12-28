#include "vertex_array.h"

#include <glad/glad.h>

static GLenum VertexBufferAttributeTypeToGL(VertexBufferAttributeType type)
{
    switch (type)
    {
    case VertexBufferAttributeType::Float:   return GL_FLOAT;
    case VertexBufferAttributeType::Float2:  return GL_FLOAT;
    case VertexBufferAttributeType::Float3:  return GL_FLOAT;
    case VertexBufferAttributeType::Float4:  return GL_FLOAT;
    case VertexBufferAttributeType::Mat3:    return GL_FLOAT;
    case VertexBufferAttributeType::Mat4:    return GL_FLOAT;
    case VertexBufferAttributeType::Int:     return GL_INT;
    case VertexBufferAttributeType::Int2:    return GL_INT;
    case VertexBufferAttributeType::Int3:    return GL_INT;
    case VertexBufferAttributeType::Int4:    return GL_INT;
    case VertexBufferAttributeType::Bool:    return GL_BOOL;
    default: ASSERT(false, "Unknown vertex buffer attribute type!"); return 0;
    }
}

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &renderer_id_);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &renderer_id_);
}

std::shared_ptr<VertexArray> VertexArray::Create()
{
    return std::make_shared<VertexArray>();
}

void VertexArray::Bind() const
{
    glBindVertexArray(renderer_id_);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
    // The vertex buffer layout has to be set before adding it to the vertex array.
    ASSERT(vertexBuffer->layout().attributes().size(), "No layout set for vertex buffer!");

    // Bind the vertex array first so that the buffer is bound to this vertex array.
    glBindVertexArray(renderer_id_);
    vertexBuffer->Bind();

    // Set all vertex buffer attributes.
    uint32_t index = 0;
    const VertexBufferLayout& layout = vertexBuffer->layout();
    for (const auto& attribute : layout)
    {
        // Specify the vertex attribute.
        glVertexAttribPointer(index,
            attribute.count(),
            VertexBufferAttributeTypeToGL(attribute.type),
            attribute.normalized ? GL_TRUE : GL_FALSE,
            layout.stride(),
            (const void*)attribute.offset);
        // Enable the vertex attribute.
        glEnableVertexAttribArray(index);

        index++;
    }

    vertex_buffers_.push_back(vertexBuffer);
}

void VertexArray::set_index_buffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
    // Bind the vertex array first so that the buffer is bound to this vertex array.
    glBindVertexArray(renderer_id_);
    indexBuffer->Bind();

    index_buffer_ = indexBuffer;
}
