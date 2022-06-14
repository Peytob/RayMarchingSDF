#ifndef __SHADER__TYPE__HPP__
#define __SHADER__TYPE__HPP__

#include <GL/glew.h>

namespace OGL {

enum ShaderType : GLenum {
    Vertex = GL_VERTEX_SHADER,
    Fragment = GL_FRAGMENT_SHADER
};

}

#endif // __SHADER__TYPE__HPP__
