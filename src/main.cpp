#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"

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

    RUN(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    RUN(glEnable(GL_BLEND));

    VertexArray vArray;

    //glClearColor(0.0f, 1.0f, 1.0f, 1.0f);  // Set clear color to cyan or any other contrasting color
    float vertices[] = {
        // x      y     z      r     g    b    
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f
    };

    
    unsigned int index[] = {
        0, 1, 2, 2, 3, 0
    };

    IndexBuffer iBuffer(index, 6);
    iBuffer.bind();

    
 

    VertexBuffer vBuffer(vertices, 20);

    Shader shader("Shader/Default.shader");
    shader.bind();

    
    vArray.linkAttrib(vBuffer, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    vArray.linkAttrib(vBuffer, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*) (3 * (sizeof(float))));
    vBuffer.bind();

    Texture texture("Resources/cat.jpg");

    texture.bind();


    shader.setUniform1f("u_scale", 0.2f);
    shader.setUniform4f("u_color", 0.0f, 0.5f, 0.8f, 1.0f);
    shader.setUniform1i("u_texture", 0);


    vBuffer.unBind();
    iBuffer.unBind();
    vArray.unBind();
    shader.unBind();

    Renderer renderer;
    
    while (!glfwWindowShouldClose(window)) {


        glClear(GL_COLOR_BUFFER_BIT);
        renderer.draw(vArray, iBuffer, shader);
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwDestroyWindow(window);
    glfwTerminate();
}