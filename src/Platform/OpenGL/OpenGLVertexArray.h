#ifndef VERTEX_ARRAY_BUFFER_H
#define VERTEX_ARRAY_BUFFER_H

#include "core.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Buffer.h"
#include "core/Mesh.h"
class OpenGLVertexArray : public VertexArray{
public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray(){};

    virtual void bind() override;
    virtual void unbind() override;

    virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
    virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

    virtual uint32_t getID() override { return m_id; };

private:

    uint32_t m_id;
    std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
    std::shared_ptr<IndexBuffer> m_indexBuffer;


};
#endif /* VERTEX_ARRAY_BUFFER_H */