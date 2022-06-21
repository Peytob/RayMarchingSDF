#ifndef __SHADER__PROGRAM_HPP__
#define __SHADER__PROGRAM_HPP__

#include <GL/glew.h>
#include <glm/vec3.hpp>

namespace OGL
{

class Shader;

class ShaderProgram {
public:

    const GLuint getId() const;
    void use();

    ~ShaderProgram();

    static ShaderProgram create(Shader vertexShader, Shader fragmentShader);

    GLint getUniformLocation(const GLchar* name);
    void setUniform(GLint location, float data);
    void setUniform(GLint location, glm::vec3 data);

private:
    ShaderProgram(GLuint id);

    const GLuint id;
};

}

#endif // __SHADER__PROGRAM_HPP__
