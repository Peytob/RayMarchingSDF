#include <glDemo/ogl/exception/ShaderProgramLinkException.hpp>

using namespace OGL;

const char* ShaderProgramLinkException::what () const throw () {
    return message.c_str();
}

const std::string ShaderProgramLinkException::getLog() const {
    return log;
}
