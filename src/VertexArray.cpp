#include <glad/glad.h>

#include "VertexArray.hpp"


VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_bufferId);
    glBindVertexArray(m_bufferId);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_bufferId);
}

void VertexArray::linkBuffer(const VertexBuffer& vBuffer, unsigned int layout) {
    vBuffer.bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
    glEnableVertexAttribArray(layout);
    vBuffer.unBind();
}

void VertexArray::bind() const {
    glBindVertexArray(m_bufferId);
}

void VertexArray::unBind() const {
    glBindVertexArray(0);
}