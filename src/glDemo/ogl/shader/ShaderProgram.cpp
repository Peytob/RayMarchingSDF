#include <vector>

#include <glDemo/ogl/shader/Shader.hpp>
#include <glDemo/ogl/shader/ShaderProgram.hpp>
#include <glDemo/ogl/exception/ShaderProgramLinkException.hpp>

using namespace OGL;

namespace {

static std::string getShaderProgramCompilationInfoLog(GLuint shaderProgramId) {
    GLint infoLogLength;
    glGetProgramiv(shaderProgramId, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<GLchar> infoLog(infoLogLength + 1);
    glGetProgramInfoLog(shaderProgramId, infoLogLength, &infoLogLength, &infoLog[0]);
    return std::string(infoLog.begin(), infoLog.end());
}

}

ShaderProgram::ShaderProgram(GLuint id) : id(id) {
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(id);
}

ShaderProgram ShaderProgram::create(Shader vertexShader, Shader fragmentShader) {
    // TODO Check is shaders really vertex and fragment
    GLint shaderProgramId = glCreateProgram();
    glAttachShader(shaderProgramId, vertexShader.getId());
    glAttachShader(shaderProgramId, fragmentShader.getId());
    glLinkProgram(shaderProgramId);

    GLint isLinked;
    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
        std::string infoLog = getShaderProgramCompilationInfoLog(shaderProgramId);
        glDeleteProgram(shaderProgramId);
        throw ShaderProgramLinkException(infoLog);
    }

    return ShaderProgram(shaderProgramId);
}

const GLuint ShaderProgram::getId() const {
    return id;
}
