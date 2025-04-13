#pragma once

class IndexBuffer{

private:
    unsigned int m_bufferId;
    unsigned int m_dataSize;

public:
    IndexBuffer(const void* data, unsigned int size);
    ~IndexBuffer();
    const void bind();
    const void unBind();

};