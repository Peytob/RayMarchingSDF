#include <glDemo/ogl/buffer/VertexArray.hpp>

using namespace OGL;

VertexArray::VertexArray(GLuint id) : id(id) {}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &id);
}

void VertexArray::bind() {
    glBindVertexArray(id);
}

void VertexArray::enableAttribute(const VertexArrayAttribute& attribute) {
    glVertexAttribPointer(
        attribute.getIndex(),
        attribute.getSize(),
        attribute.getType(),
        attribute.isNormalized(),
        attribute.getStride(),
        attribute.getPointer());

    glEnableVertexAttribArray(attribute.getIndex());
}

VertexArray VertexArray::create() {
    GLuint id;
    glCreateVertexArrays(1, &id);
    return VertexArray(id);
}
