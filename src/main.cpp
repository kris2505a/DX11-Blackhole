//Built-In Headers
#include  <glad/glad.h>
#include <GLFW/glfw3.h>

//Custom Headers
#include <VertexBuffer.hpp>
#include <IndexBuffer.hpp>
#include <Shader.hpp>
#include <VertexArray.hpp>

int main() {

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

    constexpr float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

    constexpr unsigned int indices[] = {
        0, 1, 2
    };

    VertexBuffer vBuffer(vertices, sizeof(vertices));
    IndexBuffer iBuffer(indices, sizeof(indices));
    Shader shader("shaders/BasicShader.shad");
    VertexBufferLayout vBufferLayout;
    vBufferLayout.push(3, GL_FLOAT, GL_FALSE);

    VertexArray vArray;

    vArray.bind();
    vArray.addBuffer(vBuffer, vBufferLayout);
    vBuffer.unbind();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        shader.bind();
        vArray.bind();
        vBuffer.bind();
        iBuffer.bind();

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}