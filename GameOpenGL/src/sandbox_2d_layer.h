#pragma once

#include "core/layers/layer.h"
#include "ecs/entity.h"
#include "ecs/scene.h"
#include "renderer/orthographic_camera_controller.h"
#include "renderer/shader.h"
#include "renderer/texture.h"
#include "renderer/vertex_array.h"


class Sandbox2DLayer : public Layer
{
public:
	Sandbox2DLayer();
	virtual ~Sandbox2DLayer() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(DeltaTime deltaTime) override;
	void OnEvent(Event& event) override;

private:
	// Temporary, this should be moved to the 2D renderer.
	std::shared_ptr<Shader> flat_color_shader_;
	std::shared_ptr<VertexArray> vertex_array_;
	std::shared_ptr<Texture2D> texture_;

	OrthographicCameraController camera_controller_;

	std::shared_ptr<Scene> active_scene_;

	Entity square_entity_;
	Entity camera_entity_;
};