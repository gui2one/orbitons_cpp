#ifndef VERTEX_ARRAY_BUFFER_H
#define VERTEX_ARRAY_BUFFER_H

#include "core/buffers/VertexArray.h"
#include "core/buffers/Buffer.h"
class OpenGLVertexArray : public VertexArray{
public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray(){};

    virtual void bind(){}
    virtual void unbind(){}

    virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
    virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

private:

    uint32_t m_id;
    std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
    std::shared_ptr<IndexBuffer> m_indexBuffer;


};
#endif /* VERTEX_ARRAY_BUFFER_H */