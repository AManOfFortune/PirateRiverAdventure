#include "sandbox_2d_layer.h"

#include "core/core.h"
#include "scripts/camera_controller.h"

#include <glm/gtc/matrix_transform.hpp>

Sandbox2DLayer::Sandbox2DLayer()
    : Layer("Sandbox2D")
{ }


void Sandbox2DLayer::OnAttach()
{
    sprite_sheet_ = Texture2D::Create("assets/textures/brick_tiles.png");
    sprite_sheet_normals_ = Texture2D::Create("assets/textures/brick_normals.png");

    tile_texture_ = SubTexture2D::CreateFromCoords(sprite_sheet_, { 0, 0 }, { 16, 16 });

    auto normal = SubTexture2D::CreateFromCoords(sprite_sheet_normals_, { 0, 0 }, { 16, 16 });
    auto props = Texture2DProperties(normal);

    // Create a framebuffer.
    FramebufferSpecification spec;
    // Hardcoded for now.
    spec.width = 1280;
    spec.height = 720;
    framebuffer_ = Framebuffer::Create(spec);

    active_scene_ = std::make_shared<Scene>();
    square_entity_ = active_scene_->CreateEntity("Square");
    square_entity_.AddComponent<SpriteRendererComponent>(tile_texture_, props);

    camera_entity_ = active_scene_->CreateEntity("Camera");
    camera_entity_.AddComponent<CameraComponent>();

    light_entity_ = active_scene_->CreateEntity("Light", glm::vec3(0.5f, -0.5f, 0.0f));
    light_entity_.AddComponent<LightComponent>(glm::vec3(0.8f, 0.2f, 0.3f), 0.5f);
    // Add a script to the camera entity and bind it to the ScriptableEntity subclass CameraController.
    camera_entity_.AddComponent<ScriptComponent>().Bind<CameraController>();
}

void Sandbox2DLayer::OnDetach()
{

}

void Sandbox2DLayer::OnUpdate(DeltaTime deltaTime)
{
    framebuffer_->Bind();
    RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    RenderCommand::Clear();

    // In here the DrawQuad calls are made.
    active_scene_->OnUpdate(deltaTime);

    framebuffer_->Unbind();
}

void Sandbox2DLayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Sandbox2DLayer::OnWindowResized, this, std::placeholders::_1));
}

bool Sandbox2DLayer::OnWindowResized(WindowResizeEvent& event)
{
    active_scene_->OnResize(event.width(), event.height());
    return false;
}
