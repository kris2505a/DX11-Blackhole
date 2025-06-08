#include "VertexBuffer.hpp"
#include <glad/glad.h>

VertexBuffer::VertexBuffer(const void *vertices, unsigned int size) : m_bufferId(0) {
    glGenBuffers(1, &m_bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    unbind();
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_bufferId);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}