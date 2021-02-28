#ifndef ENTITY_3D_H
#define ENTITY_3D_H

#include "../pch.h"

class Entity3d{
private:

public:

    Entity3d();
    std::string m_name;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::mat4 transforms;

    void applyTransforms();

    void setScale(glm::vec3 _scale);
};
#endif /* ENTITY_3D_H */