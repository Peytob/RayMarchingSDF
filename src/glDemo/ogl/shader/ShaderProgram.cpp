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

static std::map<std::string, GLint> searchShaderProgramUniforms(GLuint shaderProgramId) {
    std::map<std::string, GLint> uniforms; 

    GLint uniformsCount;
    glGetProgramiv(shaderProgramId, GL_ACTIVE_UNIFORMS, &uniformsCount);

    std::vector<GLchar> nameData(256);
    for (GLint uniform = 0; uniform < uniformsCount; ++uniform) {
        GLint arraySize;
        GLenum type;
        GLsizei actualLength;
        glGetActiveUniform(shaderProgramId, uniform, nameData.size(), &actualLength, &arraySize, &type, &nameData[0]);
        std::string name((char*)&nameData[0], actualLength);

        GLint location = glGetUniformLocation(shaderProgramId, name.c_str());
        uniforms.insert({ name, location });
    }

    return uniforms;
}

}

ShaderProgram::ShaderProgram(GLuint id, std::map<std::string, GLint> uniforms) : id(id), uniforms(uniforms) {
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

    std::map<std::string, GLint> uniforms = searchShaderProgramUniforms(shaderProgramId);

    return ShaderProgram(shaderProgramId, uniforms);
}

void ShaderProgram::use() {
    glUseProgram(id);
}

GLint ShaderProgram::getUniformLocation(const std::string& name) const {
    auto uniform = uniforms.find(name);

    if (uniform != uniforms.end()) {
        return uniform->second;
    }

    return -1;
}

void ShaderProgram::setUniform(const std::string& name, float data) {
    glUniform1f(getUniformLocation(name), data);
}

void ShaderProgram::setUniform(const std::string& name, const glm::vec2& data) {
    glUniform2fv(getUniformLocation(name), 1, &data[0]);
}

void ShaderProgram::setUniform(const std::string& name, const glm::vec3& data) {
    glUniform3fv(getUniformLocation(name), 1, &data[0]);
}

const GLuint ShaderProgram::getId() const {
    return id;
}

const std::map<std::string, GLint>& ShaderProgram::getUniforms() const {
    return uniforms;
}
