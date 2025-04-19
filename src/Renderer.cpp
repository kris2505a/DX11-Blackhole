#include "Renderer.hpp"

void Renderer::draw(const VertexArray& vArray, const IndexBuffer& iBuffer, const Shader& shader) {
	shader.bind();
	vArray.bind();
	iBuffer.bind();

	RUN(glDrawElements(GL_TRIANGLES, iBuffer.getCount(), GL_UNSIGNED_INT, nullptr));
	
	shader.unBind();
	vArray.unBind();
	iBuffer.unBind();
}
