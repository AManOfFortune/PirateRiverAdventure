#pragma once

#include "utils.h"

#include <cstdint>
#include <string>
#include <vector>

/// <summary>
/// Specifies all possible types a vertex buffer attribute can have.
/// </summary>
enum class VertexBufferAttributeType
{
    None = 0,  //  GLSL Types:
    Float,     //  float
    Float2,    //  vec2
    Float3,    //  vec3
    Float4,    //  vec4
    Mat3,      //  mat3, mat3x3
    Mat4,      //  mat4, mat4x4
    Int,       //  int
    Int2,      //  ivec2
    Int3,      //  ivec3
    Int4,      //  ivec4
    Bool       //  bool
};

static uint32_t VertexBufferAttributeTypeSize(VertexBufferAttributeType type)
{
    switch (type)
    {
        case VertexBufferAttributeType::Float:   return 4;
        case VertexBufferAttributeType::Float2:  return 4 * 2;
        case VertexBufferAttributeType::Float3:  return 4 * 3;
        case VertexBufferAttributeType::Float4:  return 4 * 4;
        case VertexBufferAttributeType::Mat3:    return 4 * 3 * 3;
        case VertexBufferAttributeType::Mat4:    return 4 * 4 * 4;
        case VertexBufferAttributeType::Int:     return 4;
        case VertexBufferAttributeType::Int2:    return 4 * 2;
        case VertexBufferAttributeType::Int3:    return 4 * 3;
        case VertexBufferAttributeType::Int4:    return 4 * 4;
        case VertexBufferAttributeType::Bool:    return 1;
        default: ASSERT(false, "Unknown vertex buffer attribute type!"); return 0;
    }
}

/// <summary>
/// A vertex buffer attribute which is part of a vertex buffer layout.
/// </summary>
struct VertexBufferAttribute
{
    VertexBufferAttribute(VertexBufferAttributeType type, const std::string& name, bool normalized = false)
        : type(type), name(name), size(VertexBufferAttributeTypeSize(type)), offset(0), normalized(normalized) {}

    uint32_t count() const
    {
        switch (type)
        {
            case VertexBufferAttributeType::Float:   return 1;
            case VertexBufferAttributeType::Float2:  return 2;
            case VertexBufferAttributeType::Float3:  return 3;
            case VertexBufferAttributeType::Float4:  return 4;
            case VertexBufferAttributeType::Mat3:    return 3 * 3;
            case VertexBufferAttributeType::Mat4:    return 4 * 4;
            case VertexBufferAttributeType::Int:     return 1;
            case VertexBufferAttributeType::Int2:    return 2;
            case VertexBufferAttributeType::Int3:    return 3;
            case VertexBufferAttributeType::Int4:    return 4;
            case VertexBufferAttributeType::Bool:    return 1;
            default: ASSERT(false, "Unknown vertex buffer attribute type!"); return 0;
        }
    }

    VertexBufferAttributeType type;
    std::string name;
    uint32_t size;
    uint32_t offset;
    bool normalized;
};

/// <summary>
/// The layout of a vertex buffer.
/// </summary>
class VertexBufferLayout
{
public:
    // Default constructor is needed for vertex buffer.
    VertexBufferLayout() {}
    // The initializer list makes it possible that the VertexBufferLayout can be initialized like a vector.
    VertexBufferLayout(const std::initializer_list<VertexBufferAttribute>& attributes)
        : attributes_(attributes) 
    {
        CalculateOffsetsAndStride();
    }

    inline const std::vector<VertexBufferAttribute>& attributes() const { return attributes_; }
    inline uint32_t stride() const { return stride_; }

    // These iterators are created so that a VertexBufferLayout object can be iterated over with a range based for loop.
    std::vector<VertexBufferAttribute>::iterator begin() { return attributes_.begin(); }
    std::vector<VertexBufferAttribute>::iterator end() { return attributes_.end(); }
    std::vector<VertexBufferAttribute>::const_iterator begin() const { return attributes_.begin(); }
    std::vector<VertexBufferAttribute>::const_iterator end() const { return attributes_.end(); }

private:
    void CalculateOffsetsAndStride()
    {
        uint32_t offset = 0;
        stride_ = 0;

        for (auto& attribute : attributes_)
        {
            // Set the offset of the attribute.
            attribute.offset = offset;

            // Update offset and stride values.
            offset += attribute.size;
            stride_ += attribute.size;
        }
    }

    std::vector<VertexBufferAttribute> attributes_;
    uint32_t stride_;
};
