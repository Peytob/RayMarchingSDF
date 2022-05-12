#include <vector>

#include <glDemo/ogl/shader/Shader.hpp>
#include <glDemo/ogl/exception/ShaderCompilationException.hpp>

using namespace OGL;

namespace {

static std::string getShaderCompilationLogMessage(GLuint shaderId) {
    GLint infoLogLength;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> messageChars(infoLogLength + 1);
    glGetShaderInfoLog(shaderId, infoLogLength, nullptr, &messageChars[0]);
    return std::string(messageChars.begin(), messageChars.end());
}

}

Shader Shader::create(ShaderType type, std::string code) {
    GLuint shaderId = glCreateShader(type);

    char const* codePointer = code.c_str();
    glShaderSource(shaderId, 1, &codePointer, nullptr);
    glCompileShader(shaderId);

    GLint isCompiled;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        std::string logMessage = getShaderCompilationLogMessage(shaderId);
        throw ShaderCompilationException(code, logMessage);
    }

    return Shader(shaderId, type);
}

Shader::Shader(GLuint id, ShaderType type) : id(id), type(type) { }

Shader::~Shader() {
    glDeleteShader(id);
}

const ShaderType Shader::getShaderType() const {
    return type;
}

const GLuint Shader::getId() const {
    return id;
}
