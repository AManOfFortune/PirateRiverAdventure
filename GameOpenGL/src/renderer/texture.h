#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

struct Texture2DProperties
{
    Texture2DProperties()
        : tilingFactor(1.0f), tintColor(1.0f, 1.0f, 1.0f, 1.0f)
    { }

    Texture2DProperties(float tilingFactor, const glm::vec4& tintColor)
        : tilingFactor(tilingFactor), tintColor(tintColor)
    { }

    float tilingFactor;
    glm::vec4 tintColor;
};

/// <summary>
/// Abstract base texture class.
/// </summary>
class Texture
{
public:
    virtual ~Texture() = default;

    virtual void Bind(uint32_t slot = 0) const = 0;

    virtual uint32_t width() const = 0;
    virtual uint32_t height() const = 0;
};

/// <summary>
/// Class for 2D textures that inherits from the abstract texture class. 
/// Any logic that is exclusive to 2D textures should be defined in this class.
/// </summary>
class Texture2D : public Texture
{
public:
    Texture2D(uint32_t width, uint32_t height);
    Texture2D(const std::string& path);
    ~Texture2D();

    static std::shared_ptr<Texture2D> Create(uint32_t width, uint32_t height);
    static std::shared_ptr<Texture2D> Create(const std::string& path);

    /// <summary>
    /// This method is used to upload a block of memory to the GPU.
    /// </summary>
    void SetData(void* data, uint32_t size);

    void Bind(uint32_t slot = 0) const override;

    bool operator==(const Texture2D& other) const;

    uint32_t width() const override { return width_; }
    uint32_t height() const override { return height_; }

private:
    std::string path_;
    uint32_t renderer_id_, width_, height_;
    GLenum internal_format_, data_format_;
};

/// <summary>
/// Wrapper class for a Texture2D with texture coordinate information for rendering a subtexture of a sprite sheet.
/// </summary>
class SubTexture2D
{
public:
    /// <summary>
    /// Creates a subtexture from a sprite sheet. If the given bounds are { 0.0f, 0.0f } and { 1.0f, 1.0f }, the entire texture will be used.
    /// 
    /// </summary>
    /// <param name="texture">The source texture.</param>
    /// <param name="min">Minimum bounds of the subtexture.</param>
    /// <param name="max">Maximum bounds of the subtexture.</param>
    SubTexture2D(const std::shared_ptr<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);

    static std::shared_ptr<SubTexture2D> Create(const std::shared_ptr<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);
    /// <summary>
    /// Creates a subtexture at given sprite sheet coordinates with a given subtexture size to calculate the bounds.
    /// </summary>
    /// <param name="texture">The source texture.</param>
    /// <param name="coords">The sprite sheet coordinates (0, 0) starts at the bottom left.</param>
    /// <param name="size">The size of the subtextures in the sprite sheet.</param>
    /// <returns></returns>
    static std::shared_ptr<SubTexture2D>CreateFromCoords(const std::shared_ptr<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& size);

    void Bind(uint32_t slot = 0) const;

    const std::shared_ptr<Texture2D>& texture() const { return texture_; }
    const glm::vec2* texture_coords() const { return texture_coords_; }

private:
    std::shared_ptr<Texture2D> texture_;
	glm::vec2 texture_coords_[4];
};