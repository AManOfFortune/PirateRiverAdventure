#pragma once

#include "core/layers/layer.h"
#include "ecs/entity.h"
#include "ecs/scene.h"
#include "renderer/orthographic_camera_controller.h"
#include "renderer/shader.h"
#include "renderer/texture.h"
#include "renderer/vertex_array.h"
#include "renderer/frame_buffer.h"


class GameLayer : public Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	void OnAttach() override;

	void OnUpdate(DeltaTime deltaTime) override;
	void OnEvent(Event& event) override;

private:
	std::shared_ptr<Scene> active_scene_;

	std::shared_ptr<Framebuffer> framebuffer_;
	Entity camera_entity_;

	bool OnWindowResized(WindowResizeEvent& event);

	void CreateEntities();
};
