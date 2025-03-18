#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"


int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(1280, 720, "Voxel Engine", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);


    if (glewInit() != GLEW_OK) {
        std::cout << "Unable to init glew" << std::endl;
        return 0;
    }

    RUN(glEnableVertexAttribArray(0));

    float positions[] = {
         0.5f,  0.5f,
        -0.5f, -0.5f,
         0.5f, -0.5f,
        -0.5f,  0.5f
    };
   
    VertexBuffer vBuffer(positions, 4);
    vBuffer.bind();
    
    unsigned int indexPos[] = {
        1, 2, 3, 0, 2, 3
    };
    
    IndexBuffer iBuffer(indexPos, 6);
    iBuffer.bind();
    

    RUN(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

    Shader shader("Shaders/justashader.shd");
    shader.bind();


    glViewport(0, 0, 1280, 720);

    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        RUN(glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_INT, nullptr));

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}