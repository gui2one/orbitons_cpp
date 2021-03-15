#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "core.h"
#include "Buffer.h"

namespace Orbitons{
    class VertexArray{
    public:
        virtual ~VertexArray(){}

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
        virtual void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

        virtual uint32_t getID() = 0;

        static Ref<VertexArray> create();
    private:

    };
}
#endif /* VERTEX_ARRAY_H */