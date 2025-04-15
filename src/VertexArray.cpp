#include <glad/glad.h>

#include "VertexArray.hpp"
#include "Renderer.hpp"

unsigned int VertexArray::getSize(unsigned int type) {
    switch (type) {
    case GL_FLOAT: return 4;
    case GL_UNSIGNED_INT: return 4;
    case GL_UNSIGNED_BYTE: return 1;
    }
    return 0;
}


VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_bufferId);
    RUN(glBindVertexArray(m_bufferId));
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_bufferId);
}

void VertexArray::linkAttrib(const VertexBuffer& vBuffer, unsigned int layout, unsigned int components, unsigned int type, unsigned int stride, void* offset) {
    vBuffer.bind();
    RUN(glVertexAttribPointer(layout, components, type, GL_FALSE, stride, offset));
    RUN(glEnableVertexAttribArray(layout));
    vBuffer.unBind();
}


void VertexArray::bind() const {
    RUN(glBindVertexArray(m_bufferId));
}

void VertexArray::unBind() const {
    glBindVertexArray(0);
}