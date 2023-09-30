#pragma once

#include <glm/glm.hpp>
#include <string>

/// <summary>
/// This class represents a shader program comprised of a vertex and a fragment shader.
/// </summary>
class Shader
{
public:
    Shader(const std::string& vertexSource, const std::string& fragmentSource);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    /// <summary>
    /// Sets a uniform of type mat4 with given name and value.
    /// </summary>
    void UploadUniformMat4(const std::string& name, const glm::mat4& value);

private:
    /// <summary>
    /// Creates a shader program from the given vertex and fragment shader source code.
    /// </summary>
    void CreateShader(const std::string& vertexSource, const std::string& fragmentSource);
    /// <summary>
    /// Compiles a shader of specified type from its source and assigns it to the appropriate handle (vertex_ or fragment_). 
    /// </summary>
    void CompileShader(const std::string& source, unsigned int type);
    /// <summary>
    /// Links the vertex and fragment shaders to a shader program and stores its handle in renderer_id_.
    /// </summary>
    void LinkShaderProgram();

    uint32_t renderer_id_, vertex_, fragment_;
};