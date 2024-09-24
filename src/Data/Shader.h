#pragma once
#include "Renderer.h"
#include "glm/gtc/matrix_transform.hpp"

#include <string>
#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include <sstream>
#include <unordered_map>

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	uint32_t m_RendererID;
	std::unordered_map<std::string, int32_t> m_UniformLocationCached;
public:
	Shader();
	~Shader();

	void Bind() const;
	void Unbind() const;

	//Set uniforms
	void SetUniformMat4f(const std::string& name, glm::mat4& matrix);
	void SetUniform1i(const std::string& name, uint32_t v);
	void SetUniform1f(const std::string& name, float v);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
private:
	int32_t GetUniformLocation(const std::string &name);
	ShaderProgramSource ParseShader(const std::string& filepath);
	uint32_t CompileShader(uint32_t type, const std::string& source);
	uint32_t CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};