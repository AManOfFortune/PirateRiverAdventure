#pragma once

#include "orthographic_camera.h"

class Renderer2D
{
public:
	// Equivalent to constructor and destructor.
	static void Init();
	static void Shutdown();

	// Flow of the renderer:
	// 1. Begin the scene.
	// 2. Submit the geometry.
	// 3. End the scene.
	static void BeginScene(const OrthographicCamera& camera);
	static void EndScene();

	// Primitives:
	static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
	static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
private:
};

