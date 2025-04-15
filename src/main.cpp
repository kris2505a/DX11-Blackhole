#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

    // glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.1f, 0.5f, 0.7f,
         0.0f,  0.5f, 0.0f, 0.9f, 0.2f, 0.6f,
         0.5f, -0.5f, 0.0f, 0.3f, 0.8f, 0.4f
    };



    unsigned int index[] = {
        0, 1, 2
    };

    IndexBuffer iBuffer(index, 3);
    iBuffer.bind();

    
 

    VertexBuffer vBuffer(vertices, 18);


    Shader shader("Shader/Default.shader");
    shader.bind();

    

    vArray.linkAttrib(vBuffer, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    vArray.linkAttrib(vBuffer, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    vBuffer.bind();

    vBuffer.unBind();
    iBuffer.unBind();
    vArray.unBind();
    shader.unBind();

    unsigned int uniformId = glGetUniformLocation(shader.getId(), "u_scale");
    glUniform1f(uniformId, 0.5f);
    
    while (!glfwWindowShouldClose(window)) {
        
        vArray.bind();
        vBuffer.bind();
        iBuffer.bind();
        shader.bind();

        glClear(GL_COLOR_BUFFER_BIT);
        RUN(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0));
        glfwSwapBuffers(window);
        glfwPollEvents();

    }


    glfwDestroyWindow(window);
    glfwTerminate();
}