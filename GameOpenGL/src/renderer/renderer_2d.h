#pragma once

#include "camera.h"
#include "light.h"
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
	static void BeginScene(const Camera& camera, const glm::mat4& transform);
	static void BeginScene(const OrthographicCamera& camera);  // TODO: Remove this camera parameter later.
	static void EndScene();
	static void Flush();

	// The API distinguishes between non-rotated and rotated quads because there is a slight overhead to rotating the quads.

	// Primitives:
	static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
	static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	// Other methods that are possible in the future could take in both a texture and a color.
	// Doing that would make it possible to give the textures a color tint or fade them in and out.
	static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, const Texture2DProperties& textureProperties = Texture2DProperties(), const LightProperties& lightProperties = LightProperties());
	static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, const Texture2DProperties& textureProperties = Texture2DProperties(), const LightProperties& lightProperties = LightProperties());

	static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
	static void DrawQuad(const glm::mat4& transform, const std::shared_ptr<Texture2D>& texture, const Texture2DProperties& textureProperties = Texture2DProperties(), const LightProperties& lightProperties = LightProperties());

	static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<SubTexture2D>& sub, const Texture2DProperties& textureProperties = Texture2DProperties(), const LightProperties& lightProperties = LightProperties());
	static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<SubTexture2D>& sub, const Texture2DProperties& textureProperties = Texture2DProperties(), const LightProperties& lightProperties = LightProperties());
	static void DrawQuad(const glm::mat4& transform, const std::shared_ptr<SubTexture2D>& sub, const Texture2DProperties& textureProperties = Texture2DProperties(), const LightProperties& lightProperties = LightProperties());


	// Rotation is in radians.
	static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
	static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
	static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, const Texture2DProperties& textureProperties = Texture2DProperties(), const LightProperties& lightProperties = LightProperties());
	static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, const Texture2DProperties& textureProperties = Texture2DProperties(), const LightProperties& lightProperties = LightProperties());

	static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const std::shared_ptr<SubTexture2D>& sub, const Texture2DProperties& textureProperties = Texture2DProperties(), const LightProperties& lightProperties = LightProperties());
	static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const std::shared_ptr<SubTexture2D>& sub, const Texture2DProperties& textureProperties = Texture2DProperties(), const LightProperties& lightProperties = LightProperties());

private:
	static void FlushAndReset();
};

