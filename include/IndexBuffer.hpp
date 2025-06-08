#pragma once

class IndexBuffer {
private:
   unsigned int m_bufferId;

public:
   IndexBuffer(const void* indices, unsigned int size);
   ~IndexBuffer();

   void bind() const;
   void unbind() const;
};