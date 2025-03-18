#pragma once


class VertexBuffer {
	
private:
	unsigned int m_renderId;

public:
	VertexBuffer(const void* data, int verticesCount);
	void bind();
	void unBind();
	~VertexBuffer();
};