#include "Shader.hpp"
#include <glad/glad.h>
#include <sstream>
#include <iostream>
#include <fstream>

Shader::Shader(std::string path) : m_shaderPath(std::move(path)), m_programId(0) {
    ShaderSource shaderSrc = parseShader(m_shaderPath);
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, shaderSrc.vertexShader);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, shaderSrc.fragmentShader);
    m_programId = glCreateProgram();
    glAttachShader(m_programId, vertexShader);
    glAttachShader(m_programId, fragmentShader);
    glLinkProgram(m_programId);
    glValidateProgram(m_programId);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unbind();
}

Shader::~Shader() {
    glDeleteProgram(m_programId);
}

ShaderSource Shader::parseShader(std::string &path) {
    std::ifstream shaderFile(path);
    if (!shaderFile.is_open())
        std::cerr << "Unable to open file: " << path << std::endl;

    std::stringstream buffer[2];
    std::string line;
    int type {0}; //0-VERTEX SHADER, 1-FRAGMENT SHADER

    while (getline(shaderFile, line)) {

        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos)
                type = 0;
            else if (line.find("fragment") != std::string::npos)
                type = 1;
        }

        else {
            buffer[type] << line << "\n";
        }
    }

    return {buffer[0].str(), buffer[1].str() };
}

unsigned int Shader::compileShader(unsigned int type, std::string &shaderSrc) {
    unsigned int shaderId = glCreateShader(type);
    const char* src = &shaderSrc[0];
    glShaderSource(shaderId, 1, &src, nullptr);
    glCompileShader(shaderId);

    //TODO: error handling
    return shaderId;
}

void Shader::bind() const {
    glUseProgram(m_programId);
}

void Shader::unbind() const {
    glUseProgram(0);
}

