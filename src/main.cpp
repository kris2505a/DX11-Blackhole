#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb_image.h>

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "Renderer.hpp"

const unsigned int c_width{ 800 };
const unsigned int c_height{ 600 };

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(c_width, c_height, "UnnamedGL", nullptr, nullptr);

    if(window == nullptr) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGL()) {
        std::cout << "Failed to init GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, c_width, c_height);

    VertexArray vArray;

    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);  // Set clear color to cyan or any other contrasting color
    float vertices[] = {
        // x      y     z      r     g    b    
        -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f
    };

    
    unsigned int index[] = {
        0, 1, 2, 2, 3, 0
    };

    IndexBuffer iBuffer(index, 6);
    iBuffer.bind();

    
 

    VertexBuffer vBuffer(vertices, 24);

    Shader shader("Shader/Default.shader");
    shader.bind();

    
    vArray.linkAttrib(vBuffer, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vArray.linkAttrib(vBuffer, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vArray.linkAttrib(vBuffer, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vBuffer.bind();



    unsigned int uniformId = glGetUniformLocation(shader.getId(), "u_scale");
    glUniform1f(uniformId, 0.2f);

    int imgWidth, imgHeight, numColCh;
    unsigned char* bytes = stbi_load("resources/wallnut.png", &imgWidth, &imgHeight, &numColCh, 0);
    
    unsigned int texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    RUN(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes));
    RUN(glGenerateMipmap(GL_TEXTURE_2D));

    unsigned int tex0c = glGetUniformLocation(shader.getId(), "tex0");
    glUniform1i(tex0c, 0);

    stbi_image_free(bytes);
    // glBindTexture(GL_TEXTURE_2D, 0);
    

    vBuffer.unBind();
    iBuffer.unBind();
    vArray.unBind();
    shader.unBind();
    
    while (!glfwWindowShouldClose(window)) {
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        vArray.bind();
        vBuffer.bind();
        iBuffer.bind();
        shader.bind();

        glClear(GL_COLOR_BUFFER_BIT);
        RUN(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glDeleteTextures(1, &texture);
    glfwDestroyWindow(window);
    glfwTerminate();
}