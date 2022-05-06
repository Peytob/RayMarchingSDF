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

    GLint vertexShader = loadShader("./resources/vertex.glsl", GL_VERTEX_SHADER);
    GLint fragmentShader = loadShader("./resources/fragment.glsl", GL_FRAGMENT_SHADER);

    GLint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint isLinked;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
        GLint infoLogLength;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<GLchar> infoLog(infoLogLength + 1);
        glGetProgramInfoLog(shaderProgram, infoLogLength, &infoLogLength, &infoLog[0]);
        glDeleteProgram(shaderProgram);
        std::exit(1);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

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

    GLuint vertexBuffer, vertexArray, elementBuffer;
    glGenVertexArrays(1, &vertexArray);
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &elementBuffer);
    glBindVertexArray(vertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0);

    /* Main cycle */

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.88f, 0.0f, 0.88f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vertexArray);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
    }

    glDeleteProgram(shaderProgram);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &elementBuffer);
    glDeleteVertexArrays(1, &vertexArray);

    glfwTerminate();

    return 0;
}