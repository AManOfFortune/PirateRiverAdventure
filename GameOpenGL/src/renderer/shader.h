#pragma once

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

typedef unsigned int GLenum;

/// <summary>
/// This class represents a shader program comprised of a vertex and a fragment shader.
/// </summary>
class Shader
{
public:
    Shader(const std::string& filepath);
    Shader(const std::string& vertexSource, const std::string& fragmentSource);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    // Uniform methods to set a uniform of type with given name and value.
    void UploadUniformInt(const std::string& name, int value);

    void UploadUniformFloat(const std::string& name, float value);
    void UploadUniformFloat2(const std::string& name, const glm::vec2& vec);
    void UploadUniformFloat3(const std::string& name, const glm::vec3& vec);
    void UploadUniformFloat4(const std::string& name, const glm::vec4& vec);

    void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
    void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

private:
    /// <summary>
    /// Reads the shader source code from the given filepath and returns it as a string.
    /// </summary>
    std::string ReadShaderFile(const std::string& filepath);
    /// <summary>
    /// Processes the shader source code and returns a map of shader type and its source code.
    /// </summary>
    std::unordered_map<GLenum, std::string> PreprocessShaders(const std::string& source);
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