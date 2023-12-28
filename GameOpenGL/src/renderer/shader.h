#pragma once

#include <glm/glm.hpp>
#include <memory>
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
    Shader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
    ~Shader();

    static std::shared_ptr<Shader> Create(const std::string& filepath);
    static std::shared_ptr<Shader> Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);

    void Bind() const;
    void Unbind() const;

    // These methods are not tied to the OpenGL API and are a more high level abstraction.
    // For now they simply delegate to the UploadUniform methods. Once a material system is in place
    // these methods will be used to set the uniforms of a material and do more than simply call 
    // the UploadUniform methods.
    void SetInt(const std::string& name, int value);
    void SetFloat3(const std::string& name, const glm::vec3& value);
    void SetFloat4(const std::string& name, const glm::vec4& value);
    void SetMat4(const std::string& name, const glm::mat4& value);

    // Uniform methods to set a uniform of type with given name and value.
    // These are low level methods that represent the OpenGL calls.
    void UploadUniformInt(const std::string& name, int value);
    void UploadUniformFloat(const std::string& name, float value);
    void UploadUniformFloat2(const std::string& name, const glm::vec2& vec);
    void UploadUniformFloat3(const std::string& name, const glm::vec3& vec);
    void UploadUniformFloat4(const std::string& name, const glm::vec4& vec);
    void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
    void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

    const std::string& name() const { return name_; }

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
    std::string name_;
};

class ShaderLibrary
{
public:
    /// <summary>
    /// Adds a shader program to the library.
    /// </summary>
    void Add(const std::shared_ptr<Shader>& shader);
    /// <summary>
    /// Adds a shader program to the library with the given name.
    /// </summary>
    void Add(const std::string& name, const std::shared_ptr<Shader>& shader);
    /// <summary>
    /// Load a shader from the given filepath and add it to the library.
    /// The name of the shader is the filename without the extension.    
    /// </summary>
    std::shared_ptr<Shader> Load(const std::string& filepath);
    /// <summary>
    /// Load a shader from the given filepath and add it to the library.
    /// The name of the shader is the given name.
    /// </summary>
    std::shared_ptr<Shader> Load(const std::string& name, const std::string& filepath);
    /// <summary>
    /// Get a shader program by its unique name.
    /// </summary>
    std::shared_ptr<Shader> Get(const std::string& name);
    /// <summary>
    /// Specifies whether a shader program with the given name exists in the library.
    /// </summary>
    bool Exists(const std::string& name) const;
private:
    // Map of unique shader name and its shader program.
    std::unordered_map<std::string, std::shared_ptr<Shader>> shaders_;
};