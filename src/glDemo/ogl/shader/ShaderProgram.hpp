#ifndef __SHADER__PROGRAM_HPP__
#define __SHADER__PROGRAM_HPP__

#include <string>
#include <map>
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace OGL
{

class Shader;

class ShaderProgram {
public:

    const GLuint getId() const;
    void use();

    ~ShaderProgram();

    static ShaderProgram create(Shader vertexShader, Shader fragmentShader);

    GLint getUniformLocation(const std::string& name) const;
    void setUniform(const std::string& name, float data);
    void setUniform(const std::string& name, const glm::vec2& data);
    void setUniform(const std::string& name, const glm::vec3& data);

    const std::map<std::string, GLint>& getUniforms() const;

private:
    ShaderProgram(GLuint id, std::map<std::string, GLint> uniforms);

    const GLuint id;
    const std::map<std::string, GLint> uniforms;
};

}

#endif // __SHADER__PROGRAM_HPP__
