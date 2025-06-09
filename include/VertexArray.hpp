#pragma once
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray {
private:
    unsigned int m_bufferId;

public:
    VertexArray();
    ~VertexArray() = default;
    void addBuffer(const VertexBuffer& vBuffer, const VertexBufferLayout& vBufferLayout);

    void bind() const;
    void unbind() const;
};