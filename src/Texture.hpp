#pragma once

#include "Renderer.hpp"

class Texture {
	
private:
	unsigned int m_textureId;
	std::string m_filePath;
	unsigned char* m_localBuffer;

	int m_width, m_height, m_BPP;

public:
	Texture(const std::string& path);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unBind() const;

	inline int getWidth() const { return m_width; }
	inline int getHeight() const { return m_height; }

};