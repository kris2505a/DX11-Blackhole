#include "IndexBuffer.hpp"
#include <glad/glad.h>

IndexBuffer::IndexBuffer(const void *indices, unsigned int size) : m_bufferId(0) {
    glGenBuffers(1, &m_bufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    unbind();
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_bufferId);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}