#pragma once

class IndexBuffer {

private:
	unsigned int m_renderId;

public:
	IndexBuffer(const void* data, int indexCount);
	~IndexBuffer();
	void bind();
	void unBind();
};