#include "Shader.h"
#include <iostream>
#include <fstream>
#include <glad/glad.h>

Shader::Shader(const std::string& filepath)
	: m_FilePath(filepath), m_RendererID(0)
{
	std::cout << "Shader file path: " << filepath << std::endl;
	std::string vertexShader = ParseShader(filepath + ".vertex");
	std::string fragmentShader = ParseShader(filepath + ".fragment");
	m_RendererID = CreateShader(vertexShader, fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);

}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);

}

void Shader::Unbind() const
{
	glUseProgram(0);
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

signed int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

std::string Shader::ParseShader(const std::string& filepath)
{
    std::ifstream file(filepath);
    std::string str;
    std::string content;
    while (std::getline(file, str))
    {
        content.append(str + "\n");
    }
    return content;
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	int location = glGetUniformLocation(m_RendererID, name.c_str());

	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	m_UniformLocationCache[name] = location;

	return location;
}
