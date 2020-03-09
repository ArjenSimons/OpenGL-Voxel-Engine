#pragma once
#include <string>
#include <glm/glm.hpp>

struct ShaderProgramSource
{
	std::string VertexSource, FragmentSource;
};

class Shader {
private:
	std::string m_Filepath;
	unsigned int m_RendererId;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	std::string GetFilepath() const { return m_Filepath; }
private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);
public:
	unsigned int SetMat4(const char* attribName, glm::mat4 mvp);
};
