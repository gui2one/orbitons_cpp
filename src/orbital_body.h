#ifndef ORBITAL_BODY_H
#define ORBITAL_BODY_H

#include "pch.h"
#include "core.h"
namespace Orbitons{


class OrbitalBody{
public:
    OrbitalBody();
    ~OrbitalBody();

private:
    glm::vec3 m_position;
    glm::vec3 m_velocity;

    float radius;
    float mass;
};
};

#endif /* ORBITAL_BODY_H */