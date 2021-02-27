#ifndef OBJECT_3D_H
#define OBJECT_3D_H

#include "Entity3d.h"
#include "Material.h"
#include "Mesh.h"
class Object3d : public Entity3d{
public:
    Mesh m_mesh;
    std::shared_ptr<Material> m_material; 
private:

};
#endif /* OBJECT_3D_H */