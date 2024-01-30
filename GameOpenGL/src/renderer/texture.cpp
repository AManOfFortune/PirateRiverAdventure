#include "texture.h"

#include "core/utils.h"

#include <glad/glad.h>
#include <stb_image.h>

Texture2D::Texture2D(uint32_t width, uint32_t height)
    : width_(width), height_(height)
{
    // Set the internal and data formats depending on the number of color channels.
    internal_format_ = GL_RGBA8; 
    data_format_ = GL_RGBA;

    // Generate a texture.
    glGenTextures(1, &renderer_id_);
    // Bind the 2D texture.
    glBindTexture(GL_TEXTURE_2D, renderer_id_);

    // Set magnification and minification filters.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  // GL_NEAREST selects the texel (texture pixel) center that is closest to the texture coordinate.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // GL_LINEAR linearly interpolates between the neighbouring texels to create an approximated color.\

    // Set the texture wrapping parameters to repeat the texture image.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Texture2D::Texture2D(const std::string& path)
    : path_(path)
{
    // Flip the image vertically. This needs to be done because the stb_image library reads the image data top to bottom and OpenGL bottom to top.
    stbi_set_flip_vertically_on_load(true);

    int width, height, channels;
    // Load the file with given path and store its width, height and channel information in the given arguments.
    stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    ASSERT(data, "Failed to load image!");

    width_ = width;
    height_ = height;

    // Set the internal and data formats depending on the number of color channels.
    GLenum internalFormat = 0, dataFormat = 0;
    switch (channels)
    {
    case 3:
        // RGB for 3 channels
        internalFormat = GL_RGB8;
        dataFormat = GL_RGB;
        break;
    case 4:
        // RGBA for 4 channels
        internalFormat = GL_RGBA8;
        dataFormat = GL_RGBA;
        break;
    }

    internal_format_ = GL_RGBA8;
    data_format_ = GL_RGBA;

    ASSERT(internalFormat, "Internal format not supported!");
    ASSERT(dataFormat, "Data format not supported");

    // Generate a texture.
    glGenTextures(1, &renderer_id_);
    // Bind the 2D texture.
    glBindTexture(GL_TEXTURE_2D, renderer_id_);

    // Set magnification and minification filters.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  // GL_NEAREST selects the texel (texture pixel) center that is closest to the texture coordinate.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // GL_LINEAR linearly interpolates between the neighbouring texels to create an approximated color.\

    // Set the texture wrapping parameters to repeat the texture image.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Upload the texture image.
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width_, height_, 0, dataFormat, GL_UNSIGNED_BYTE, data);

    // Generate a mipmap for the texture.
    glGenerateMipmap(GL_TEXTURE_2D);

    // Free the memory on the CPU.
    stbi_image_free(data);
}

Texture2D::~Texture2D()
{
    // Delete the texture.
    glDeleteTextures(1, &renderer_id_);
}

std::shared_ptr<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
{
    return std::make_shared<Texture2D>(width, height);
}

std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path)
{
    return std::make_shared<Texture2D>(path);
}

void Texture2D::SetData(void* data, uint32_t size)
{
    uint32_t bytesPerPixel = data_format_ == GL_RGBA ? 4 : 3;
    ASSERT(size == width_ * height_ * bytesPerPixel, "Incorrect data size!");
    glTexImage2D(GL_TEXTURE_2D, 0, internal_format_, width_, height_, 0, data_format_, GL_UNSIGNED_BYTE, data);
}

void Texture2D::Bind(uint32_t slot) const
{
    // Activate the texture slot.
    glActiveTexture(GL_TEXTURE0 + slot);
    // Bind the texture.
    glBindTexture(GL_TEXTURE_2D, renderer_id_);
}

bool Texture2D::operator==(const Texture2D& other) const
{
    return renderer_id_ == other.renderer_id_;
}

SubTexture2D::SubTexture2D(const std::shared_ptr<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
    : texture_(texture)
{
    // Set the texture coordinates.
	texture_coords_[0] = { min.x, min.y }; // Bottom left
	texture_coords_[1] = { max.x, min.y }; // Bottom right
	texture_coords_[2] = { max.x, max.y }; // Top right
	texture_coords_[3] = { min.x, max.y }; // Top left
}

std::shared_ptr<SubTexture2D> SubTexture2D::Create(const std::shared_ptr<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
{
    return std::make_shared<SubTexture2D>(texture, min, max);
}

std::shared_ptr<SubTexture2D> SubTexture2D::CreateFromCoords(const std::shared_ptr<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& size)
{
    glm::vec2 min = { (coords.x * size.x) / texture->width(), (coords.y * size.y) / texture->height() }; // Bottom left
    glm::vec2 max = { ((coords.x + 1) * size.x) / texture->width(), ((coords.y + 1) * size.y) / texture->height() }; // Top right
    return Create(texture, min, max);
}

void SubTexture2D::Bind(uint32_t slot) const
{
    texture_->Bind(slot);
}
