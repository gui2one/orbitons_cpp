#include "OpenGLVertexArray.h"


OpenGLVertexArray::OpenGLVertexArray(){
    glCreateVertexArrays(1, &m_id);
}

void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer){
    for(const auto& element : vertexBuffer->getLayout().getElements()){
        printf("  - name : %s\n", element.Name.c_str());
    }
}


void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer){
     m_indexBuffer = indexBuffer; 
}
