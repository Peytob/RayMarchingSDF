#ifndef __SHADER__COMPILATION__EXCEPTION__HPP__
#define __SHADER__COMPILATION__EXCEPTION__HPP__

#include <string>

#include <exception>

namespace OGL
{

class ShaderCompilationException: public std::exception {
public:
    ShaderCompilationException(std::string code, std::string log) :
        code(code),
        log(log),
        message("Shader has been not compiled. Compilation log: " + log) { }

    const char* what () const throw () override;

    const std::string getCode() const;

    const std::string getLog() const;

private:
    const std::string code;
    const std::string log;
    const std::string message;
};

}

#endif
