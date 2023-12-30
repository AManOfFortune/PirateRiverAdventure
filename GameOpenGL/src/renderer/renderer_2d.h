#pragma once

#include "orthographic_camera.h"
#include "texture.h"

#include <memory>

struct Texture2DProperties
{
	Texture2DProperties()
		: tilingFactor(1.0f), tintColor(1.0f, 1.0f, 1.0f, 1.0f)
	{ }

	Texture2DProperties(float tilingFactor, const glm::vec4& tintColor)
		: tilingFactor(tilingFactor), tintColor(tintColor)
	{ }

	float tilingFactor;
	glm::vec4 tintColor;
};

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

	// The API distinguishes between non-rotated and rotated quads because there is a slight overhead to rotating the quads.

	// Primitives:
	static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
	static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	// Other methods that are possible in the future could take in both a texture and a color.
	// Doing that would make it possible to give the textures a color tint or fade them in and out.
	static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, const Texture2DProperties& textureProperties = Texture2DProperties());
	static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, const Texture2DProperties& textureProperties = Texture2DProperties());

	static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
	static void DrawQuad(const glm::mat4& transform, const std::shared_ptr<Texture2D>& texture, const Texture2DProperties& textureProperties = Texture2DProperties());

	// Rotation is in radians.
	static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
	static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
	static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, const Texture2DProperties& textureProperties = Texture2DProperties());
	static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, const Texture2DProperties& textureProperties = Texture2DProperties());

private:
};

