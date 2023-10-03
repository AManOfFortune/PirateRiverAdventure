#pragma once

#include <cstdint>
#include <string>

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
    Texture2D(const std::string& path);
    ~Texture2D();

    void Bind(uint32_t slot = 0) const override;

    uint32_t width() const override { return width_; }
    uint32_t height() const override { return height_; }

private:
    std::string path_;
    uint32_t renderer_id_, width_, height_;
};