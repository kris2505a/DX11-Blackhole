#include <glad/glad.h>

#include "Shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

enum ShaderType {
    VERTEX, FRAGMENT
};

Shader::Shader(const std::string& path) {
    m_shaderPath = path;

    ShaderSource shaderSrc = this->parseShader();
    unsigned int vertexShader = this->compileShader(GL_VERTEX_SHADER, shaderSrc.vertexShaderSrc);
    unsigned int fragmentShader = this->compileShader(GL_FRAGMENT_SHADER, shaderSrc.fragmentShaderSrc);

    this->m_shaderId = glCreateProgram();
    glAttachShader(m_shaderId, vertexShader);
    glAttachShader(m_shaderId, fragmentShader);
    glLinkProgram(m_shaderId);
    glValidateProgram(m_shaderId);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

ShaderSource Shader::parseShader() {

    std::ifstream shaderFile(m_shaderPath);
    if(!shaderFile.is_open()) {
        std::cout << "unable to open file" << std::endl;
        return {"none", "none"};
    }

    std::stringstream ss[2];
    ShaderType type;

    std::string line;
    while(getline(shaderFile, line)) {
        if(line.find("#shader") != std::string::npos) {
            if(line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else {
            ss[type] << line << "\n";
        }
    }
    return {ss[0].str(), ss[1].str()};
    
}

unsigned int Shader::compileShader(unsigned int shaderType, const std::string& shaderSource) {
    unsigned int shader = glCreateShader(shaderType);
    const char* src = &shaderSource[0];
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    return shader;
}

Shader::~Shader() {
    glDeleteProgram(m_shaderId);
}

const void Shader::bind() {
    glUseProgram(m_shaderId);
}

const void Shader::unBind() {
    glUseProgram(0);
}