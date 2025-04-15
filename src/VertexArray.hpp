#pragma once

#include "VertexBuffer.hpp"

class VertexArray {
private:
    unsigned int m_bufferId;

public:

    static unsigned int getSize(unsigned int type);
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unBind() const;
    
    void linkAttrib(const VertexBuffer& vBuffer, unsigned int layout, unsigned int components, GLenum type, unsigned int stride, void* offset);
    
};