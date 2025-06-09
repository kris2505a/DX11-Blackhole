#pragma once
#include <complex>
#include  <vector>

#define GL_FLOAT 0x1406
#define GL_UNSIGNED_INT 0x1405
#define GL_UNSIGNED_BYTE 0x1401
#define GL_FALSE 0
#define GL_TRUE 1

struct BufferElements {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int getSizeOf(const unsigned int type) {
        switch (type) {
            case GL_FLOAT:
            case GL_UNSIGNED_INT:  return 4;
            case GL_UNSIGNED_BYTE: return 1;
            default:               return 4;
        }
    }
};

class VertexBufferLayout {
private:
    std::vector <BufferElements> m_elements;
    unsigned int m_stride;

public:
    VertexBufferLayout() : m_stride(0) {}
    ~VertexBufferLayout() = default;

    template <typename T> inline void push(unsigned int count) { static_assert(false, "Unsupported format"); }

    inline void push(unsigned int count, unsigned int type, unsigned char normalized) {
        m_elements.push_back({type, count, normalized});
        m_stride += count * BufferElements::getSizeOf(type);
    }

    inline const std::vector <BufferElements>& getElements() const { return m_elements; }

    inline unsigned int getStride() const {
        return m_stride;
    }

};