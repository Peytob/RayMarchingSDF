#ifndef __VERTEX__ARRAY__HPP__
#define __VERTEX__ARRAY__HPP__

#include <GL/glew.h>

#include <glDemo/ogl/buffer/VertexArrayAttribute.hpp>

namespace OGL {

class VertexArray {
public:
    ~VertexArray();

    void bind();
    void enableAttribute(const VertexArrayAttribute& attribute);

    static VertexArray create();

private:
    VertexArray(GLuint id);
    const GLuint id;
};

}

#endif
