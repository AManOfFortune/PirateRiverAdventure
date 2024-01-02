#pragma once

#include <memory>

struct FramebufferSpecification
{
	uint32_t width = 0, height = 0;
	// Abstracts the call to glBindFramebuffer(0) which basically unbinds all framebuffers and renders to the screen.
	// This allows to create a framebuffer that doesn't really exist (?) which is important for a future concept called
	// "Render Passes". A render pass always contains a target framebuffer to render to. If the target framebuffer
	// has isSwapChainTarget set to false, the render pass will render to the screen.
	bool isSwapChainTarget = false;
};

class Framebuffer
{
public:
	Framebuffer(const FramebufferSpecification& spec);
	virtual ~Framebuffer();

	static std::shared_ptr<Framebuffer> Create(const FramebufferSpecification& spec);

	// Specifies the state to be invalid so that it is recreated.
	void Invalidate();

	void Bind();
	void Unbind();

	inline FramebufferSpecification& specification() { return specification_; }
	inline const FramebufferSpecification& specification() const { return specification_; }

	inline uint32_t color_attachment_renderer_id() const { return color_attachment_; }

private:
	FramebufferSpecification specification_;
	uint32_t renderer_id_ = 0;
	uint32_t color_attachment_ = 0;
	uint32_t depth_attachment_ = 0;
};