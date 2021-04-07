#ifndef MESH_OBJECT_H
#define MESH_OBJECT_H

#include "core.h"
#include "Core/Mesh.h"

#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Material.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
namespace Orbitons
{
    class MeshObject
    {
    public:
        Mesh m_mesh;

        std::shared_ptr<VertexBuffer> m_vertexBuffer;
        std::shared_ptr<IndexBuffer> m_indexBuffer;
        Orbitons::Ref<VertexArray> m_vertexArray;
        GLuint vao;

    public:
        MeshObject();
        MeshObject(const Mesh &mesh);
        void buildBuffers();
        void draw();
        void setMesh(const Mesh &mesh);

    private:
        uint64_t m_num_elements;
    };
} // namespace Orbitons

#endif /* MESH_OBJECT_H */