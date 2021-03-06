#include "MeshObject.h"
#include "Core/MeshUtils.h"
namespace Orbitons
{
    MeshObject::MeshObject()
    {
    }

    MeshObject::MeshObject(const Mesh &mesh)
        : m_mesh(mesh)
    {
        buildBuffers();
    }

    void MeshObject::setMesh(const Mesh &mesh)
    {
        m_mesh = mesh;

        // MeshUtils::computeNormals(m_mesh);
        buildBuffers();
    }

    void MeshObject::buildBuffers()
    {

        m_vertexBuffer.reset(VertexBuffer::create((float *)m_mesh.vertices.data(), m_mesh.vertices.size() * sizeof(Vertex)));
        // m_vertexBuffer->bind();

        BufferLayout layout = {
            {ShaderDataType::Float3, "position"},
            {ShaderDataType::Float3, "normal"},
            {ShaderDataType::Float2, "t_coords"}};

        m_vertexBuffer->setLayout(layout);
        m_vertexArray = VertexArray::create();
        m_vertexArray->addVertexBuffer(m_vertexBuffer);

        m_indexBuffer.reset(IndexBuffer::create(m_mesh.indices.data(), m_mesh.indices.size() * sizeof(int)));
        m_vertexArray->setIndexBuffer(m_indexBuffer);
        // m_indexBuffer->bind();

        m_num_elements = m_mesh.indices.size();
        // m_mesh.vertices.clear();
        // m_mesh.indices.clear();
    }

    void MeshObject::draw()
    {
        glBindVertexArray(m_vertexArray->getID());
        glDrawElements(GL_TRIANGLES, m_num_elements, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }
} // namespace Orbitons
