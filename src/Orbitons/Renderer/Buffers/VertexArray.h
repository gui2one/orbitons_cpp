#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "Buffer.h"
#include "core.h"

class VertexArray{
public:
    virtual ~VertexArray(){}

    virtual void bind() = 0;
    virtual void unbind() = 0;

    virtual void addVertexBuffer(const Orbitons::Ref<VertexBuffer>& vertexBuffer) = 0;
    virtual void setIndexBuffer(const Orbitons::Ref<IndexBuffer>& indexBuffer) = 0;

    virtual uint32_t getID() = 0;

    static Orbitons::Ref<VertexArray> create();
private:

};
#endif /* VERTEX_ARRAY_H */