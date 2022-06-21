#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glDemo/ogl/shader/Shader.hpp>
#include <glDemo/ogl/shader/ShaderProgram.hpp>

#include <glDemo/ogl/buffer/Buffer.hpp>
#include <glDemo/ogl/buffer/VertexArray.hpp>

using namespace OGL;

std::string loadFile(const std::string& path) {
    std::ifstream fileStream(path);
    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    return buffer.str();
}

Shader loadShader(const std::string& path, ShaderType shaderType) {
    GLint shaderId = glCreateShader(shaderType);
    std::string code = loadFile(path);

    return Shader::create(shaderType, code);
}

int main()
{
    /* GLFW and GLEW initialization; creating window */

    if (glfwInit() != GLFW_TRUE) {
        const char* errorDescription;
        const int errorCode = glfwGetError(&errorDescription);
        std::cerr << "Error while GLFW initializating!" << std::endl;
        std::cerr << "Error code: " << errorCode << "; error description: " << errorDescription << std::endl;
        std::exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Some window", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    const GLenum glewInitializationCode = glewInit();
    if (glewInitializationCode != GLEW_OK) {
        std::cerr << "Error while GLEW initialzing!" << std::endl;
        std::cerr << glewGetErrorString(glewInitializationCode) << std::endl;
        std::exit(1);
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    /* Loading shader program */

    Shader vertexShader = loadShader("./resources/vertex.glsl", ShaderType::Vertex);
    Shader fragmentShader = loadShader("./resources/fragment.glsl", ShaderType::Fragment);
    ShaderProgram shaderProgram = ShaderProgram::create(vertexShader, fragmentShader);
    GLint timeUniformLocation = shaderProgram.getUniformLocation("time");

    /* Rect initialization */

    float vertices[] = {
         1.0f,  1.0f,
         1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f,  1.0f
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    VertexArray vertexArray = VertexArray::create();
    vertexArray.bind();

    Buffer vertexBuffer = Buffer::create(BufferType::Array);
    vertexBuffer.bind();
    vertexBuffer.loadData(sizeof(vertices), vertices);

    Buffer elementBuffer = Buffer::create(BufferType::ElementArray);
    elementBuffer.bind();
    elementBuffer.loadData(sizeof(indices), indices);

    auto attribute = VertexArrayAttribute(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    vertexArray.enableAttribute(attribute);

    /* Main cycle */

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        std::cout << timeUniformLocation << " " << glfwGetTime() << std::endl;

        glClearColor(0.88f, 0.0f, 0.88f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();
        shaderProgram.setUniform(timeUniformLocation, glfwGetTime());
        vertexArray.bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
