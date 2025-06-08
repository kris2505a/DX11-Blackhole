#pragma once
#include <string>

struct ShaderSource {
    std::string vertexShader;
    std::string fragmentShader;
};

class Shader {
private:
    unsigned int m_programId;
    std::string m_shaderPath;

    ShaderSource parseShader(std::string& path);
    unsigned int compileShader(unsigned int type, std::string& shaderSrc);

public:
    Shader(std::string path);
    ~Shader();

    void bind() const;
    void unbind() const;
};