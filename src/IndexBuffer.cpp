#include <GL/glew.h>

#include "IndexBuffer.hpp"
#include "Renderer.hpp"

#include <GLFW/glfw3.h>

IndexBuffer::IndexBuffer(const void* data, int indexCount) {
    RUN(glGenBuffers(1, &m_renderId));
    RUN(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderId));
    RUN(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {

}

void IndexBuffer::bind() {
    RUN(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderId));
}

void IndexBuffer::unBind() {
    RUN(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}