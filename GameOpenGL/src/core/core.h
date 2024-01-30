#pragma once

// -- Core ---------------------------------
#include "core/application.h"
#include "core/layers/layer.h"
#include "core/log.h"

#include "core/delta_time.h"

#include "core/input/input.h"
#include "core/input/key_codes.h"
#include "core/input/mouse_button_codes.h"
// -----------------------------------------

// -- ECS ----------------------------------
#include "ecs/components.h"
#include "ecs/entity.h"
#include "ecs/scriptable_entity.h"
#include "ecs/scene.h"
// -----------------------------------------

// -- Renderer -----------------------------
#include "renderer/renderer.h"
#include "renderer/renderer_2d.h"
#include "renderer/render_command.h"

#include "renderer/light.h"
#include "renderer/shader.h"
#include "renderer/texture.h"

#include "renderer/frame_buffer.h"
#include "renderer/index_buffer.h"
#include "renderer/vertex_buffer.h"
#include "renderer/vertex_buffer_layout.h"
#include "renderer/vertex_array.h"

#include "renderer/orthographic_camera.h"
#include "renderer/orthographic_camera_controller.h"
// -----------------------------------------
