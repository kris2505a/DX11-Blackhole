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

    window = glfwCreateWindow(800, 600, "Voxel Engine", nullptr, nullptr);
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
         -0.5f, -0.5f, //t1 1
         -0.25f, 0.0f, //t1 2, t3 1
          0.0f, -0.5f, //t1 3, t2 1
          0.25f, 0.0f, //t2 2, t3 3
          0.5f, -0.5f, //t2 3
          0.0f,  0.5f //t3 2
    };
   
    VertexBuffer vBuffer(positions, 8);
    vBuffer.bind();
    
    unsigned int indexPos[] = {
        0, 1, 2, 2, 3, 4, 1, 5, 3
    };
    
    IndexBuffer iBuffer(indexPos, 9);
    iBuffer.bind();
    

    RUN(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

    Shader shader("Shaders/justashader.shd");   
    shader.bind();


    //glViewport(0, 0, 1280, 720);

    glClearColor(0.0f, 0.3f, 0.5f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        RUN(glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr));

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}