#include "Object3d.h"

Object3d::Object3d() : Entity3d(){
    m_material = Orbitons::MakeRef<PhongMaterial>();
   
}

void Object3d::buildBuffers(){

    m_vertexBuffer.reset(VertexBuffer::create((float *)m_mesh.vertices.data(), m_mesh.vertices.size() * sizeof(Vertex)));
    m_vertexBuffer->bind();

    BufferLayout layout = {
      { ShaderDataType::Float3, "position" },
      { ShaderDataType::Float3, "normal" },
      { ShaderDataType::Float2, "t_coords" }
    };

    m_vertexBuffer->setLayout(layout);
    m_vertexArray = VertexArray::create();
    m_vertexArray->addVertexBuffer(m_vertexBuffer);
    m_vertexArray->setIndexBuffer(m_indexBuffer);


    m_indexBuffer.reset(IndexBuffer::create(m_mesh.indices.data(), m_mesh.indices.size() * sizeof(int) ));
    m_indexBuffer->bind();

}

void Object3d::draw(){

    m_material->useProgram();
    glBindVertexArray(m_vertexArray->getID());
    glDrawElements(GL_TRIANGLES, m_mesh.indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
    glUseProgram(0);
}