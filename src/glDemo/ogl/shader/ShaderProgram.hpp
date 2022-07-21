#ifndef __SHADER__PROGRAM_HPP__
#define __SHADER__PROGRAM_HPP__

#include <string>
#include <map>
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
    void setUniform(const std::string& location, float data);
    void setUniform(const std::string& location, glm::vec3 data);

    const std::map<const std::string, GLint>& getUniforms() const;

private:
    ShaderProgram(GLuint id, std::map<const std::string, GLint>& uniforms);

    const GLuint id;
    const std::map<const std::string, GLint> uniforms;

    GLint getUniformLocation(const std::string& location) const;
};

}

#endif // __SHADER__PROGRAM_HPP__
