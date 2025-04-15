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
    unsigned int compileShader(unsigned int shaderType, const std::string& shaderSource);

public:
    Shader(const std::string& path = "Shader/Default.shader");
    ~Shader();
    void bind() const;
    void unBind() const;
    unsigned int getId() const;

};