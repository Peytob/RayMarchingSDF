#ifndef __BUFFER_HPP__
#define __BUFFER_HPP__

#include <GL/glew.h>
#include <glDemo/ogl/buffer/BufferType.hpp>

namespace OGL {

class Buffer {
public:
    ~Buffer();

    void bind();
    void loadData(GLsizeiptr size, const void* data);

    const GLuint getId() const;

    static Buffer create(BufferType type);

private:
    Buffer(GLuint id, BufferType type);

    const GLuint id;
    const BufferType type;
};

}

#endif
