#ifndef __VERTEX__ARRAY__ATTRIBUTE__HPP__
#define __VERTEX__ARRAY__ATTRIBUTE__HPP__

#include <GL/glew.h>

namespace OGL {

class VertexArrayAttribute {
public:
    VertexArrayAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) :
        index(index), type(type), size(size), normalized(normalized), stride(stride), pointer(pointer) {};

    const GLuint getIndex() const;
    const GLint getSize() const;
    const GLenum getType() const;
    const GLboolean isNormalized() const;
    const GLsizei getStride() const;
    const void* getPointer() const;

private:
    const GLuint index;
    const GLint size;
    const GLint type;
    const GLboolean normalized;
    const GLsizei stride;
    const void* pointer;
};

}

#endif
