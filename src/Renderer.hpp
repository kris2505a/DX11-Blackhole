#pragma once
#include <glad/glad.h>
#include <iostream>

#define ASSERT(x) if(!(x)) std::abort();
#define RUN(x) glClearError(); \
               x; \
               ASSERT(glLogCall(#x, __FILE__, __LINE__))


static void glClearError() {
    while (glGetError() != GL_NO_ERROR);
}

static bool glLogCall(const char* function, const char* file, int line) {
    while(GLenum error = glGetError()) {
        std::cout << "[Error]: " << error << std::endl;
        std::cout << function << " - " << file << " - " << line << std::endl;
        return false;
    }
    return true;
}