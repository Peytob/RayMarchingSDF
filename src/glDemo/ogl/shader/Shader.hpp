#ifndef __SHADER__HPP__
#define __SHADER__HPP__

#include <string>

#include <GL/glew.h>

#include <glDemo/ogl/shader/ShaderType.hpp>

namespace OGL {

class Shader {
public:
    ~Shader();

    const ShaderType getShaderType() const;

    const GLuint getId() const;

    static Shader create(ShaderType type, std::string code);

private:
    Shader(GLuint id, ShaderType type);

    const GLuint id;
    const ShaderType type;
};

}

#endif // __SHADER__HPP__
