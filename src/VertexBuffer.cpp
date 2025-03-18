#include <GL/glew.h>
#include "VertexBuffer.hpp"
#include "Renderer.hpp"
#include <GLFW/glfw3.h>

VertexBuffer::VertexBuffer(const void* data, int verticesCount) {
	RUN(glGenBuffers(1, &m_renderId));
	RUN(glBindBuffer(GL_ARRAY_BUFFER, m_renderId));
	RUN(glBufferData(GL_ARRAY_BUFFER, 2 * verticesCount * sizeof(float), data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
	
}

void VertexBuffer::bind() {
	RUN(glBindBuffer(GL_ARRAY_BUFFER, m_renderId));
}

void VertexBuffer::unBind() {
	RUN(glBindBuffer(GL_ARRAY_BUFFER, 0));
}