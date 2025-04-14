#pragma once

class VertexBuffer {

private:
    unsigned int m_bufferId;
    unsigned int m_dataSize;

public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();
    void bind() const;
    void unBind() const;
};