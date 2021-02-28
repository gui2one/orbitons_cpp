#ifndef OBJECT_3D_H
#define OBJECT_3D_H

#include "Entity3d.h"
#include "Material.h"
#include "Mesh.h"
#include "../core.h"
class Object3d : public Entity3d{
public:

    Object3d();
    void buildVBO();
    void draw();
    Mesh m_mesh;
    std::shared_ptr<Material> m_material; 

    GLuint vbo, vao, ibo;
private:

};
#endif /* OBJECT_3D_H */