#pragma once
#include <string>

struct Shaders {
	std::string vertexShader, fragmentShader;
};

class Shader {
	
private:
	unsigned int m_programId;
	std::string m_path;
	Shaders m_shader;

	Shaders parseShader();
	unsigned int compileShader(unsigned int shaderType, const std::string& shader);
	unsigned int createShader();


public:
	Shader(std::string path);
	~Shader();
	void bind();
	void unBind();

};

