#include "VertexArray.hpp"
#include <glad/glad.h>

VertexArray::VertexArray() : m_bufferId(0) {
    glGenVertexArrays(1, &m_bufferId);
    glBindVertexArray(m_bufferId);
    unbind();
}



void VertexArray::bind() const {
    glBindVertexArray(m_bufferId);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}

void VertexArray::addBuffer(const VertexBuffer &vBuffer, const VertexBufferLayout &vBufferLayout) {

    vBuffer.bind();
    unsigned int offset = 0;

    auto elements = vBufferLayout.getElements();

    for (int i = 0 ; i < elements.size() ; i++) {
        auto element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(
            i,
            element.count,
            element.type,
            element.normalized,
            vBufferLayout.getStride(),
            (const void*) offset
        );
        offset += element.count * BufferElements::getSizeOf(element.type);
    }
    vBuffer.unbind();
}


