#pragma once
#include <string>

struct ShaderSource {
    std::string vertexShaderSrc, fragmentShaderSrc;
};

class Shader {

private:
    unsigned int m_shaderId;
    std::string m_shaderPath;
    ShaderSource parseShader();

public:
    Shader(const std::string& path = "Shader/Default.shader");
    ~Shader();
    const void bind();
    const void unBind();

};