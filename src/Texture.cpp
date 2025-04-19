#include "Texture.hpp"
#include "Renderer.hpp"

#define GL_CLAMP 0x2900


#include "thirdparty/stb_image.hpp"
#include <gl/GL.h>

Texture::Texture(const std::string& path)
	: m_textureId(0), m_filePath(path), m_localBuffer(nullptr), m_width(0), m_height(0), m_BPP(0){
	
	stbi_set_flip_vertically_on_load(1);
	RUN(glGenTextures(1, &m_textureId));
	RUN(glBindTexture(GL_TEXTURE_2D, m_textureId));

	m_localBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_BPP, 4);
	RUN(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	RUN(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	RUN(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	RUN(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	RUN(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));

	this->unBind();
	if (m_localBuffer) {
		stbi_image_free(m_localBuffer);
	}
}

Texture::~Texture() {
	RUN(glDeleteTextures(1, &m_textureId));
}

void Texture::bind(unsigned int slot) const {
	RUN(glActiveTexture(GL_TEXTURE0 + slot))
	RUN(glBindTexture(GL_TEXTURE_2D, m_textureId));
}

void Texture::unBind() const {
	RUN(glBindTexture(GL_TEXTURE_2D, 0));
}
