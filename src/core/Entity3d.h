#ifndef ENTITY_3D_H
#define ENTITY_3D_H

#include "../pch.h"

class Entity3d{
private:

public:
    std::string m_name;
    glm::mat4 transforms;
};
#endif /* ENTITY_3D_H */