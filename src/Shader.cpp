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

Shader::~Shader() {

}

const void Shader::bind() {

}

const void Shader::unBind() {

}