#pragma once

#include "VertexBuffer.hpp"

class VertexArray {
private:
    unsigned int m_bufferId;

public:

    VertexArray();
    ~VertexArray();

    void bind() const;
    void unBind() const;
    
    void linkBuffer(const VertexBuffer& vBuffer, unsigned int layout);
    
};