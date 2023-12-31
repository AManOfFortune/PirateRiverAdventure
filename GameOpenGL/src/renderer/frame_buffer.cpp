#include "frame_buffer.h"

#include "core/utils.h"

#include <glad/glad.h>

Framebuffer::Framebuffer(const FramebufferSpecification& spec)
	: specification_(spec)
{}

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &renderer_id_);
}

std::shared_ptr<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
{
	return std::make_shared<Framebuffer>(spec);
}

void Framebuffer::Invalidate()
{
	// Generate and bind framebuffer.
	glGenFramebuffers(1, &renderer_id_);
	glBindFramebuffer(GL_FRAMEBUFFER, renderer_id_);

	// Generate color buffer attachment.
	glGenTextures(1, &color_attachment_);
	glBindTexture(GL_TEXTURE_2D, color_attachment_);
	// RGBA8: 8 bits per channel, GLRGBA32F: for HDR.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, specification_.width, specification_.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	// Set minifaction and magnification filters.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Attach the color attachment to the framebuffer.
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_attachment_, 0);

	// Generate depth buffer attachment.
	glGenTextures(1, &depth_attachment_);
	glBindTexture(GL_TEXTURE_2D, depth_attachment_);
	// Stencil buffer is included here. The 24 stands for the depth buffer bit size and the 8 bit for the stencil buffer. (24 + 8 = 32)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, specification_.width, specification_.height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depth_attachment_, 0);

	ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

	// Unbind framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, renderer_id_);
}

void Framebuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
