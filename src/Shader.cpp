#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include <fstream>
#include <iostream>

#include "Renderer.hpp"
#include "Shader.hpp"

enum shaderType {
	vertex,
	fragment
};

Shader::Shader(std::string path) : m_path(path) {

	m_programId = this->createShader();
}

unsigned int Shader::createShader() {
	m_shader = this->parseShader();

	unsigned int vShader = compileShader(GL_VERTEX_SHADER, m_shader.vertexShader);
	unsigned int fShader = compileShader(GL_FRAGMENT_SHADER, m_shader.fragmentShader);

	unsigned int program = glCreateProgram();
	RUN(glAttachShader(program, vShader));
	RUN(glAttachShader(program, fShader));
	RUN(glLinkProgram(program));
	RUN(glValidateProgram(program));

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	return program;
}

Shaders Shader::parseShader() {
	std::ifstream file(m_path);
	if (!file.is_open())
		std::cout << "Unable to open file" << std::endl;
	
	std::stringstream ss[2];
	
	std::string line;
	int type;
	
	while (getline(file, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos)
				type = shaderType::vertex;

			else if (line.find("fragment") != std::string::npos)
				type = shaderType::fragment;
		}

		else {
			ss[type] << line << std::endl;
		}
	}
	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::compileShader(unsigned int shaderType, const std::string& shader) {
	unsigned int id = glCreateShader(shaderType);
	const char* src = shader.c_str();
	RUN(glShaderSource(id, 1, &src, nullptr));
	RUN(glCompileShader(id));

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (!result) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* msg = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, msg);
		std::cout << "[Shader Compile Error]:" << msg << std::endl;
	}


	return id;
}

Shader::~Shader() {
	glDeleteProgram(m_programId);
}

void Shader::bind() {
	RUN(glUseProgram(m_programId));
}

void Shader::unBind() {
	RUN(glUseProgram(0));
}