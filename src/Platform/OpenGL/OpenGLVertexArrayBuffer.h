#ifndef OPENGL_VERTEX_ARRAY_BUFFER_H
#define OPENGL_VERTEX_ARRAY_BUFFER_H

#include "core/buffers/VertexArrayBuffer.h"
class OpenGLVertexArrayBuffer : public VertexArrayBuffer{
public:

    OpenGLVertexArrayBuffer();
    virtual ~OpenGLVertexArrayBuffer(){};
    virtual void bind() override;
    virtual void unbind() override;
private:

};
#endif /* OPENGL_VERTEX_ARRAY_BUFFER_H */