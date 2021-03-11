#ifndef OBJECT_3D_H
#define OBJECT_3D_H

#include "Entity3d.h"
#include "Renderer/Material.h"
#include "Mesh.h"
#include "core.h"

#include "Renderer/Buffers/Buffer.h"
#include "Renderer/Buffers/VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
class Object3d : public Entity3d{
public:

    Object3d();
    void buildBuffers();
    void draw();
    Mesh m_mesh;
    Orbitons::Ref<Material> m_material; 

    std::shared_ptr<VertexBuffer> m_vertexBuffer;
    std::shared_ptr<IndexBuffer> m_indexBuffer;
    Orbitons::Ref<VertexArray> m_vertexArray;
    GLuint vao;
private:

};
#endif /* OBJECT_3D_H */