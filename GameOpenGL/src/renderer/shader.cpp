#include "shader.h"

#include "core/log.h"
#include "core/utils.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

static GLenum ShaderTypeFromString(const std::string& type)
{
	if (type == "vertex")
		return GL_VERTEX_SHADER;
	if (type == "fragment" || type == "pixel")
		return GL_FRAGMENT_SHADER;

	ASSERT(false, "Invalid shader type specified!");
	return 0;
}

Shader::Shader(const std::string& filepath)
{
    std::string sourceFile = ReadShaderFile(filepath);
    std::unordered_map<GLenum, std::string> shaderSources = PreprocessShaders(sourceFile);
    CreateShader(shaderSources[GL_VERTEX_SHADER], shaderSources[GL_FRAGMENT_SHADER]);

    // Extract the name of the shader from the filepath.
	size_t lastSlash = filepath.find_last_of("/\\");
    // If no slash position is 0 else it's the position after the slash.
    lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
    // Find the position of the last dot.
    size_t lastDot = filepath.rfind('.');
    // Count is the number of characters to be extracted.
    auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
    name_ = filepath.substr(lastSlash, count);
}

Shader::Shader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
	: name_(name)
{
    // Create the shader program with given vertex and fragment shaders.
    CreateShader(vertexSource, fragmentSource);
}

Shader::~Shader() 
{
    // Delete the shader program.
    glDeleteProgram(renderer_id_);
}

std::shared_ptr<Shader> Shader::Create(const std::string& filepath)
{
    return std::make_shared<Shader>(filepath);
}

std::shared_ptr<Shader> Shader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
{
    return std::make_shared<Shader>(name, vertexSource, fragmentSource);
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

std::string Shader::ReadShaderFile(const std::string& filepath)
{
    std::string result;
    std::ifstream in(filepath, std::ios::in | std::ios::binary);
    if (in)
    {
        // Sets the position of the next character to be extracted from the input stream.
        // Here , it sets the position to the end of the file.
        // https://cplusplus.com/reference/istream/istream/seekg/
        in.seekg(0, std::ios::end);
        // Returns the position of the current character in the input stream. 
        // Here, same as size of the file.
        // https://cplusplus.com/reference/istream/istream/tellg/
        result.resize(in.tellg());
        // Sets the position back to the beginning of the file.
        in.seekg(0, std::ios::beg);
        // Reads the entire file into the string.
        in.read(&result[0], result.size());
        // Closes the input stream.
        in.close();
    }
    else
    {
        // For now log an error if the shader file could not be opened.
        LOG_ERROR("Could not open file '{0}'", filepath);
    }

    return result;
}

std::unordered_map<GLenum, std::string> Shader::PreprocessShaders(const std::string& source)
{
	std::unordered_map<GLenum, std::string> shaderSources;

	const char* typeToken = "#type";
	size_t typeTokenLength = strlen(typeToken);
	size_t pos = source.find(typeToken, 0);
    while (pos != std::string::npos)
    {
		// Find the end of the line.
		size_t eol = source.find_first_of("\r\n", pos);
        // Syntax error if no end of line is found.
		ASSERT(eol != std::string::npos, "Syntax error!");

		// Get the shader type from the line. Does only work for a single whitespace character.
		size_t begin = pos + typeTokenLength + 1;
		std::string type = source.substr(begin, eol - begin);
		ASSERT(ShaderTypeFromString(type), "Invalid shader type specified!");

		// Find the beginning of the shader source code.
		size_t nextLinePos = source.find_first_not_of("\r\n", eol);
		ASSERT(nextLinePos != std::string::npos, "Syntax error!");
		pos = source.find(typeToken, nextLinePos);

		// Store the shader source code in the map.
		shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? 
            source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
	}

	return shaderSources;
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

void ShaderLibrary::Add(const std::shared_ptr<Shader>& shader)
{
    const std::string& name = shader->name();
    Add(name, shader);
}

void ShaderLibrary::Add(const std::string& name, const std::shared_ptr<Shader>& shader)
{
	ASSERT(!Exists(name), "Shader already exists!");
	shaders_[name] = shader;
}

std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& filepath)
{
    std::shared_ptr<Shader> shader = Shader::Create(filepath);
    Add(shader);
    return shader;
}

std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
{
    std::shared_ptr<Shader> shader = Shader::Create(filepath);
    Add(name, shader);
    return shader;
}

std::shared_ptr<Shader> ShaderLibrary::Get(const std::string& name)
{
    ASSERT(Exists(name), "Shader does not exist!");
    return shaders_[name];
}

bool ShaderLibrary::Exists(const std::string& name) const
{
    return shaders_.find(name) != shaders_.end();
}
