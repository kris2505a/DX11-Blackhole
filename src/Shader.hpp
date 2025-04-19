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
    unsigned int getUniform(const std::string& uniformName);

public:
    Shader(const std::string& path);
    ~Shader();
    void bind() const;
    void unBind() const;
    unsigned int getId() const;
    void setUniform4f(const std::string& uniformName, float r, float g, float b, float a);
    void setUniform1f(const std::string& uniformName, float x);
};