#include "VertexBuffer.hpp"
#include <glad/glad.h>

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    m_dataSize = size;
    glGenBuffers(1, &m_bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
    glBufferData(GL_ARRAY_BUFFER, m_dataSize * sizeof(float), data, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

const void VertexBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
}

const void VertexBuffer::unBind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_bufferId);
}