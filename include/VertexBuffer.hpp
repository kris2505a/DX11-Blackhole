#pragma once

class VertexBuffer {
private:
    unsigned int m_bufferId;

public:
    VertexBuffer(const void* vertices, unsigned int size);
    ~VertexBuffer();
    void bind() const;
    void unbind() const;
};