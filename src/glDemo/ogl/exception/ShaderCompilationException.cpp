#include <glDemo/ogl/exception/ShaderCompilationException.hpp>

using namespace OGL;

const char* ShaderCompilationException::what () const throw () {
    return message.c_str();
}

const std::string ShaderCompilationException::getCode() const {
    return code;
}

const std::string ShaderCompilationException::getLog() const {
    return log;
}
