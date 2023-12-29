#include "index_buffer.h"

#include <glad/glad.h>

IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count)
    : count_(count)
{
    glGenBuffers(1, &renderer_id_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &renderer_id_);
}

std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
{
    return std::make_shared<IndexBuffer>(indices, count);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id_);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
