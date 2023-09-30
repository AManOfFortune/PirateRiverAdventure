#pragma once

#include "orthographic_camera.h"
#include "render_command.h"
#include "shader.h"

/// <summary>
/// The renderer holds higher level rendering functionality which is independent of the rendering API
/// used since it uses our own RendererAPI class under the hood. Because we only need to worry about 
/// OpenGL the differentiation between RendererAPI and Renderer is technically not needed.
/// </summary>
class Renderer
{
public:
    /// <summary>
    /// Specifies the start of a new scene. Here all model independent data should be submitted.
    /// This includes environmental information such as the camera and lights. By doing it this
    /// way the environment of a scene is independent from the geometry/meshes inside.
    /// </summary>
    static void BeginScene(OrthographicCamera& camera);
    /// <summary>
    /// Specifies the end of the scene. Needs to be called after BeginScene.
    /// </summary>
    static void EndScene();
    /// <summary>
    /// Submits geometry/mesh data to be rendered inside the scene. Shaders could be added to 
    /// the mesh in form of materials for example. Ideally, the submitted geometry/mesh will not
    /// get rendered immediately but will instead be submitted to a render command queue that 
    /// could even be processed in other threads.
    /// </summary>
    static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

private:
    struct SceneData
    {
        glm::mat4 projectionViewMatrix;
    };

    static SceneData* sceneData;
};