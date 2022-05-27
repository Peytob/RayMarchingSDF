#ifndef __SHADER__PROGRAM__COMPILATION__ERROR__
#define __SHADER__PROGRAM__COMPILATION__ERROR__

#include <string>

#include <exception>

namespace OGL {

class ShaderProgramLinkException: public std::exception {
public:
    ShaderProgramLinkException(std::string log) :
    log(log),
    message("Shader program has been not linked.") { }

    const char* what () const throw () override;

    const std::string getLog() const;

private:
    const std::string log;
    const std::string message;
};

} // namespace OGL

#endif
