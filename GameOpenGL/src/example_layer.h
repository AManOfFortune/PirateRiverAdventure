#pragma once

#include "core/core.h"

class ExampleLayer : public Layer
{
public:
    ExampleLayer();
	virtual ~ExampleLayer() = default;

	void OnUpdate(DeltaTime deltaTime) override;
	void OnEvent(Event& event) override;

private:
    ShaderLibrary shader_library_;
    std::shared_ptr<VertexArray> vertex_array_, rectangle_vertex_array_;
    std::shared_ptr<Shader> shader_, flat_color_shader_;
    std::shared_ptr<Texture2D> checkerboard_texture_, logo_texture_;

    OrthographicCameraController camera_controller_;
};