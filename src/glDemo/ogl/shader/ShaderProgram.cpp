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

static GLint getUniformsCount(GLuint shaderProgramId) {
    GLint total;
    glGetProgramiv(shaderProgramId, GL_ACTIVE_UNIFORMS, &total); 
    return total;
}

static std::map<const std::string, GLint> searchShaderProgramUniforms(GLuint shaderProgramId) {
    GLint total = getUniformsCount(shaderProgramId);
    std::map<const std::string, GLint> uniforms; 

    for (GLint i = 0; i < total; ++i) {
        GLenum type = GL_ZERO;
        std::vector<GLchar> nameBuffer(256);
        GLint uniformNameLength;
        GLint uniformSize;
        glGetActiveUniform(shaderProgramId, GLuint(i), nameBuffer.size(), &uniformNameLength, &uniformSize, &type, &nameBuffer[0]);

        GLuint location = glGetUniformLocation(shaderProgramId, &nameBuffer[0]);
        std::string name = std::string(nameBuffer.begin(), nameBuffer.end());

        uniforms.insert({name, location});
    }

    return uniforms;
}

}

ShaderProgram::ShaderProgram(GLuint id, std::map<const std::string, GLint>& uniforms) : id(id), uniforms(std::move(uniforms)) {
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

    std::map<const std::string, GLint> uniforms = searchShaderProgramUniforms(shaderProgramId);

    return ShaderProgram(shaderProgramId, uniforms);
}

void ShaderProgram::use() {
    glUseProgram(id);
}

GLint ShaderProgram::getUniformLocation(const GLchar* name) {
    return glGetUniformLocation(id, name);
}

void ShaderProgram::setUniform(const std::string& location, float data) {
    glUniform1f(getUniformLocation(location), data);
}

void ShaderProgram::setUniform(const std::string& location, glm::vec3 data) {
    glUniform3fv(getUniformLocation(location), 1, &data[0]);
}

const GLuint ShaderProgram::getId() const {
    return id;
}

const std::map<const std::string, GLint>& ShaderProgram::getUniforms() const {
    return uniforms;
}

GLint ShaderProgram::getUniformLocation(const std::string& location) const {
    auto it = uniforms.find(location);
    if (it != uniforms.end()) {
        return it->second;
    }

    return -1;
}
