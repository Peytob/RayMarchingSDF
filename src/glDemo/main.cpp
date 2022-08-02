#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <glDemo/ogl/shader/Shader.hpp>
#include <glDemo/ogl/shader/ShaderProgram.hpp>

#include <glDemo/ogl/buffer/Buffer.hpp>
#include <glDemo/ogl/buffer/VertexArray.hpp>

#include <glDemo/utils/Camera.hpp>

int main()
{
    /* GLFW initialization */

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

    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Some window", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glewExperimental = GL_TRUE;
    const GLenum glewInitializationCode = glewInit();
    if (glewInitializationCode != GLEW_OK) {
        std::cerr << "Error while GLEW initialzing!" << std::endl;
        std::cerr << glewGetErrorString(glewInitializationCode) << std::endl;
        std::exit(1);
    }

    glfwTerminate();

    return 0;
}
