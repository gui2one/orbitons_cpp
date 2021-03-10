#ifndef OBJECT_3D_H
#define OBJECT_3D_H

#include "Entity3d.h"
#include "Material.h"
#include "Mesh.h"
#include "../core.h"

#include "buffers/Buffer.h"
#include "buffers/VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
class Object3d : public Entity3d{
public:

    Object3d();
    void buildBuffers();
    void draw();
    Mesh m_mesh;
    std::shared_ptr<Material> m_material; 

    std::unique_ptr<VertexBuffer> m_vertexBuffer;
    std::unique_ptr<IndexBuffer> m_indexBuffer;
    std::unique_ptr<VertexArray> m_vertexArray;
    GLuint vao;
private:

};
#endif /* OBJECT_3D_H */