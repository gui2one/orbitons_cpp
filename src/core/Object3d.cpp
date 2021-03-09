#include "Object3d.h"

Object3d::Object3d() : Entity3d(){
    m_material = std::make_shared<PhongMaterial>();
   
}

void Object3d::buildVBO(){

    m_vertexBuffer.reset(VertexBuffer::create((float *)m_mesh.vertices.data(), m_mesh.vertices.size() * sizeof(Vertex)));
    m_vertexBuffer->bind();



    vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0); // position --> 0 offset
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)(3* sizeof(float))); // normal --> 3 offset        
    glBindBuffer(GL_ARRAY_BUFFER, (GLuint)m_vertexBuffer->getID());


    m_indexBuffer.reset(IndexBuffer::create(m_mesh.indices.data(), m_mesh.indices.size() * sizeof(int) ));
    m_indexBuffer->bind();

}

void Object3d::draw(){


    m_material->useProgram();

    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_indexBuffer->getID());

        glDrawElements(GL_TRIANGLES, m_mesh.indices.size(), GL_UNSIGNED_INT, nullptr);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);  

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);


    glUseProgram(0);
}