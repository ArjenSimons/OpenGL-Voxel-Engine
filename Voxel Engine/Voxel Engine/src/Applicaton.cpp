#include <GL/glew.h>
#include "Window.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct ShaderProgramSource
{
	std::string VertexSource, FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath)
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

static unsigned int CompileShader(unsigned int type, const std::string& source)
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
		std::cout << "\n" << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") <<"shader compilation ERROR!" << std::endl;	
		std::cout << message << std::endl;

		glDeleteShader(id);
		return 0;
	}

	return id;
}

static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
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

int main(void)
{
	Window window = Window::Window(WindowProps());

	float positions[12]{
		-0.5f, -0.5,
		 0.5f, -0.5f,
		-0.5f,  0.5f,

		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");

	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);

	glUseProgram(shader);

	while (window.IsRunning())
	{
		/*Render*/
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 6);
		window.OnUpdate();	
	}

	glDeleteProgram(shader);
	window.Shutdown();

	return 0;
}