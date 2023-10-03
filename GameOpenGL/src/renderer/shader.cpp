#include "shader.h"

#include "log/log.h"
#include "utils.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource) 
{
    // Create the shader program with given vertex and fragment shaders.
    CreateShader(vertexSource, fragmentSource);
}

Shader::~Shader() 
{
    // Delete the shader program.
    glDeleteProgram(renderer_id_);
}

void Shader::Bind() const 
{
    glUseProgram(renderer_id_);
}

void Shader::Unbind() const 
{
    glUseProgram(0);
}

void Shader::UploadUniformInt(const std::string& name, int value)
{
    // TODO: Implement cache for the location using a hash map so look up is not performed every time.

    GLint location = glGetUniformLocation(renderer_id_, name.c_str());
    glUniform1i(location, value);
}

void Shader::UploadUniformFloat(const std::string& name, float value)
{
    // TODO: Implement cache for the location using a hash map so look up is not performed every time.

    GLint location = glGetUniformLocation(renderer_id_, name.c_str());
    glUniform1f(location, value);
}

void Shader::UploadUniformFloat2(const std::string& name, const glm::vec2& vec)
{
    // TODO: Implement cache for the location using a hash map so look up is not performed every time.

    GLint location = glGetUniformLocation(renderer_id_, name.c_str());
    glUniform2f(location, vec.x, vec.y);
}

void Shader::UploadUniformFloat3(const std::string& name, const glm::vec3& vec)
{
    // TODO: Implement cache for the location using a hash map so look up is not performed every time.

    GLint location = glGetUniformLocation(renderer_id_, name.c_str());
    glUniform3f(location, vec.x, vec.y, vec.z);
}

void Shader::UploadUniformFloat4(const std::string& name, const glm::vec4& vec)
{
    // TODO: Implement cache for the location using a hash map so look up is not performed every time.

    GLint location = glGetUniformLocation(renderer_id_, name.c_str());
    glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
}

void Shader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
{
    // TODO: Implement cache for the location using a hash map so look up is not performed every time.

    GLint location = glGetUniformLocation(renderer_id_, name.c_str());
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
{
    // TODO: Implement cache for the location using a hash map so look up is not performed every time.

    GLint location = glGetUniformLocation(renderer_id_, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::CreateShader(const std::string& vertexSource, const std::string& fragmentSource) 
{
    // Compile the vertex and fragment shaders.
    CompileShader(vertexSource, GL_VERTEX_SHADER);
    CompileShader(fragmentSource, GL_FRAGMENT_SHADER);

    // Link the compiled shaders to a shader program.
    LinkShaderProgram();
}

void Shader::CompileShader(const std::string& source, unsigned int type) 
{
    // Create an empty shader handle and store it depending on the type.
    GLuint shader;
    switch (type) 
    {
        case GL_VERTEX_SHADER:
            vertex_ = glCreateShader(type);
            shader = vertex_;
            break;
        case GL_FRAGMENT_SHADER:
            fragment_ = glCreateShader(type);
            shader = fragment_;
            break;
        default:
            ASSERT(false, "Invalid shader type!");
    }

    // Send the shader source to GL.
    const GLchar* src = source.c_str();
    glShaderSource(shader, 1, &src, 0);

    // Compile the shader.
    glCompileShader(shader);

    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) 
    {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        // maxLength includes the terminating \0.
        std::vector<GLchar> log(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &log[0]);

        // Delete the shader.
        glDeleteShader(shader);

        LOG_ERROR("{0}", log.data());
        ASSERT(false, "Shader compilation failure!");
    }
}

void Shader::LinkShaderProgram() 
{
    // Create a program.
    renderer_id_ = glCreateProgram();
    GLuint program = renderer_id_;

    // Attach the created shaders to the program.
    glAttachShader(program, vertex_);
    glAttachShader(program, fragment_);

    // Link the program.
    glLinkProgram(program);

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) 
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // maxLength includes the terminating \0.
        std::vector<GLchar> log(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &log[0]);

        // Delete the program and the shaders.
        glDeleteProgram(program);
        glDeleteShader(vertex_);
        glDeleteShader(fragment_);

        LOG_ERROR("{0}", log.data());
        ASSERT(false, "Shader linking failure!");
    }

    // Detach the shaders after linking successfully.
    glDetachShader(program, vertex_);
    glDetachShader(program, fragment_);
}
