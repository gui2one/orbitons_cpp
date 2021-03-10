#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "Buffer.h"

class VertexArray{
public:
    virtual ~VertexArray(){}

    virtual void addVertexBuffer(const VertexBuffer& vertexBuffer) = 0;
    virtual void setIndexBuffer(const IndexBuffer& indexBuffer) = 0;

    static VertexArray* create();
private:

};
#endif /* VERTEX_ARRAY_H */