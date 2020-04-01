#include "Shader.h"
#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string & filepath)
	: m_Filepath(filepath), m_RendererId(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	m_RendererId = CreateShader(source.VertexSource, source.FragmentSource);
	Bind();
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererId);
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos) //npos is invalid string position (so true if it finds #shader on line)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else ss[(int)type] << line << '\n';
	}

	return { ss[0].str(), ss[1].str() };
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

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	/*Shader Error handling*/
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "\n" << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << "shader compilation ERROR!" << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::SetTexture(const char * attribName, int value)
{
	unsigned int uniformLocation = glGetUniformLocation(m_RendererId, attribName);

	glUniform1i(uniformLocation, value);

	return uniformLocation;
}

unsigned int Shader::SetVec3(const char* attribName, glm::vec3 vector) {
	unsigned int uniformLocation = glGetUniformLocation(m_RendererId, attribName);

	glUniform3f(uniformLocation, vector.x, vector.y, vector.z);

	return uniformLocation;
}

unsigned int Shader::SetMat4(const char* attribName, glm::mat4 matrix)
{
	unsigned int uniformLocation = glGetUniformLocation(m_RendererId, attribName);

	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &matrix[0][0]);

	return uniformLocation;
}

void Shader::Bind() const
{
	glUseProgram(m_RendererId);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}
