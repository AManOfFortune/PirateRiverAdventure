#pragma once

#include "orthographic_camera.h"
#include "texture.h"

#include <memory>

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
	// Other methods that are possible in the future could take in both a texture and a color.
	// Doing that would make it possible to give the textures a color tint or fade them in and out.
	static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture);
	static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture);

private:
};

