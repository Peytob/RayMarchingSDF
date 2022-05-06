#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

int main()
{
    if (glfwInit() != GLFW_TRUE) {
        const char* errorDescription;
        const int errorCode = glfwGetError(&errorDescription);
        std::cerr << "Error while GLFW initializating!" << std::endl;
        std::cerr << "Error code: " << errorCode << "; error description: " << errorDescription << std::endl;
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
