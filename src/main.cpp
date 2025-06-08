//Built-In Headers
#include  <glad/glad.h>
#include <GLFW/glfw3.h>

//Custom Headers
#include <VertexBuffer.hpp>
#include <IndexBuffer.hpp>
#include <Shader.hpp>

int main()
{

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Test Window", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGL()) {
        glfwTerminate();
        return -1;
    }
    glViewport(0, 0, 1280, 720);
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

    const float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

    const unsigned int indices[] = {
        0, 1, 2
    };

    VertexBuffer vBuffer(vertices, sizeof(vertices));
    IndexBuffer iBuffer(indices, sizeof(indices));
    Shader shader("shaders/BasicShader.shad");

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    vBuffer.bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
    vBuffer.unbind();

    glBindVertexArray(0);



    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        shader.bind();
        glBindVertexArray(vao);
        vBuffer.bind();
        iBuffer.bind();

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}