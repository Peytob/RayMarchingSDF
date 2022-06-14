#ifndef __BUFFER__TYPE__HPP__
#define __BUFFER__TYPE__HPP__

#include <GL/glew.h>

namespace OGL {

enum BufferType : GLenum {
    Array = GL_ARRAY_BUFFER,
    ElementArray = GL_ELEMENT_ARRAY_BUFFER
};

}


#endif
