#include "IndexBuffer.hpp"
#include <glad/glad.h>
#include "Renderer.hpp"

IndexBuffer::IndexBuffer(const void* data, unsigned int size) {
    m_dataSize = size;
    glGenBuffers(1, &m_bufferId);
    RUN(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId));
    RUN(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_dataSize * sizeof(unsigned int), data, GL_STATIC_DRAW));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::bind() const {
    RUN(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId));
}

void IndexBuffer::unBind() const {
    RUN(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

IndexBuffer::~IndexBuffer() {
    RUN(glDeleteBuffers(1, &m_bufferId));
}

unsigned int IndexBuffer::getCount() const {
    return m_dataSize;
}