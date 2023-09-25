#include "buffer.h"

#include "core.h"
#include "opengl_buffer.h"
#include "renderer.h"

VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
{
    switch (Renderer::API())
    {
        case RendererAPI::kNone: ASSERT(false, "RendererAPI::kNone is not supported!"); return nullptr;
        case RendererAPI::kOpenGL: return new OpenGLVertexBuffer(vertices, size);
        default: ASSERT(false, "Unknown renderer API!"); return nullptr;
    }
}

IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
{
    switch (Renderer::API())
    {
        case RendererAPI::kNone: ASSERT(false, "RendererAPI::kNone is not supported!"); return nullptr;
        case RendererAPI::kOpenGL: return new OpenGLIndexBuffer(indices, count);
        default: ASSERT(false, "Unknown renderer API!"); return nullptr;
    }
}
