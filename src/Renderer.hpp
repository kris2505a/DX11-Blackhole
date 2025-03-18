#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak();

#define RUN(x) clearError(); \
	x;\
	ASSERT(logCall(#x, __FILE__, __LINE__))


static void clearError() {
	while (glGetError() != GL_NO_ERROR);
}

static bool logCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[Error] ->> " << error << " " << function << " " << file << " : " << line << std::endl;
		return false;
	}
	return true;
}