#ifndef VERTEX_ARRAY_BUFFER_H
#define VERTEX_ARRAY_BUFFER_H

#include "core.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Buffer.h"
#include "Core/Mesh.h"

namespace Orbitons
{

    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        virtual void bind() override;
        virtual void unbind() override;

        virtual void addVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) override;
        virtual void setIndexBuffer(const Ref<IndexBuffer> &indexBuffer) override;

        virtual uint32_t getID() override { return m_id; };

    private:
        uint32_t m_id;
        std::vector<Ref<VertexBuffer>> m_vertexBuffers;
        Ref<IndexBuffer> m_indexBuffer;
    };
}
#endif /* VERTEX_ARRAY_BUFFER_H */