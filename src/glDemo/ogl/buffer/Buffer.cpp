#include <glDemo/ogl/buffer/Buffer.hpp>

using namespace OGL;

Buffer::Buffer(GLuint id, BufferType type) : id(id), type(type) {}

Buffer::~Buffer() {
    glDeleteBuffers(1, &id);
}

Buffer Buffer::create(BufferType type) {
    GLuint id;
    glGenBuffers(1, &id);
    return Buffer(id, type);
}

void Buffer::bind() {
    glBindBuffer(type, id);
}

void Buffer::loadData(GLsizeiptr size, const void* data) {
    // TODO Usage variable
    glBufferData(type, size, data, GL_STATIC_DRAW);
}

const GLuint Buffer::getId() const {
    return id;
}
