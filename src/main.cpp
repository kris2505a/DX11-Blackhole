#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

const unsigned int c_width{ 800 };
const unsigned int c_height{ 600 };


const char* vertexShaderSrc = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 pos;\n"
    "void main() { \n"
    "gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);\n"
    "}\n\0";

const char* fragmentShaderSrc = 
    "#version 330 core\n"
    "out vec4 fragColor;\n"
    "void main() { \n"
    "fragColor= vec4(0.3f, 0.5f, 0.8f, 1.0f);\n"
    "}\n\0";


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

    unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vertexShaderSrc, nullptr);
    glCompileShader(vShader);

    unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fragmentShaderSrc, nullptr);
    glCompileShader(fShader);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);

    glLinkProgram(program);
    glValidateProgram(program);
    glUseProgram(program);


    glDeleteShader(vShader);
    glDeleteShader(fShader);


    // glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };


    unsigned int vArrayObject;
    glGenVertexArrays(1, &vArrayObject);
    glBindVertexArray(vArrayObject);

    unsigned int index[] = {
        0, 1, 2
    };

    IndexBuffer iBuffer(index, 3);
    iBuffer.bind();

    glEnableVertexAttribArray(0);


    VertexBuffer vBuffer(vertices, 9);
    vBuffer.bind();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    Shader shader("Shader/Default.shader");

    
    while (!glfwWindowShouldClose(window)) {
        
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glDeleteProgram(program);

    glfwDestroyWindow(window);
    glfwTerminate();
}