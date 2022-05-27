#ifndef __SHADER__PROGRAM_HPP__
#define __SHADER__PROGRAM_HPP__

#include <GL/glew.h>

namespace OGL
{

class Shader;

class ShaderProgram {
public:

    const GLuint getId() const;

    ~ShaderProgram();

    static ShaderProgram create(Shader vertexShader, Shader fragmentShader);
private:
    ShaderProgram(GLuint id);

    const GLuint id;
};

}

#endif // __SHADER__PROGRAM_HPP__
