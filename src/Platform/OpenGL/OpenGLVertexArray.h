#ifndef VERTEX_ARRAY_BUFFER_H
#define VERTEX_ARRAY_BUFFER_H

#include "core/buffers/VertexArray.h"
#include "core/buffers/Buffer.h"
class OpenGLVertexArray : public VertexArray{
public:
    OpenGLVertexArray(){};
    virtual ~OpenGLVertexArray(){};

    virtual void addVertexBuffer(const VertexBuffer& vertexBuffer){

    };
    virtual void setIndexBuffer(const IndexBuffer& indexBuffer){

    };

private:

};
#endif /* VERTEX_ARRAY_BUFFER_H */