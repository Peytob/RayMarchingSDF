#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

std::string loadFile(const std::string& path) {
    std::ifstream fileStream(path);
    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    return buffer.str();
}

GLint loadShader(const std::string& path, GLint shaderType) {
    GLint shaderId = glCreateShader(shaderType);
    std::string code = loadFile(path);
    char const* codePointer = code.c_str();

    glShaderSource(shaderId, 1, &codePointer, nullptr);
    glCompileShader(shaderId);

    GLint isCompiled;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> messageChars(infoLogLength + 1);
        glGetShaderInfoLog(shaderId, infoLogLength, nullptr, &messageChars[0]);
        std::string message = std::string(messageChars.begin(), messageChars.end());
        std::cerr << "Error while compiling shader: " << message << std::endl;
        std::exit(1);
    }

    return shaderId;
}

int main()
{
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

    GLint vertexShader = loadShader("./resources/vertex.glsl", GL_VERTEX_SHADER);
    GLint fragmentShader = loadShader("./resources/fragment.glsl", GL_FRAGMENT_SHADER);

    GLint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(shaderProgram);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.88f, 0.0f, 0.88f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
