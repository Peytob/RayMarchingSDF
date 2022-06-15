#include <glDemo/ogl/buffer/VertexArrayAttribute.hpp>

using namespace OGL;

const GLuint VertexArrayAttribute::getIndex() const {
    return index;
}

const GLint VertexArrayAttribute::getSize() const {
    return size;
}

const GLenum VertexArrayAttribute::getType() const {
    return type;
}

const GLboolean VertexArrayAttribute::isNormalized() const {
    return normalized;
}

const GLsizei VertexArrayAttribute::getStride() const {
    return stride;
}

const void*VertexArrayAttribute:: getPointer() const {
    return pointer;
}
