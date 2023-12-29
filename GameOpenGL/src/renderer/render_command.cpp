#include "render_command.h"

std::unique_ptr<RendererAPI> RenderCommand::renderer_api_ = std::make_unique<RendererAPI>();