#ifndef ENTITY_3D_H
#define ENTITY_3D_H

#include "../pch.h"
#include "../core.h"
#include "entt/entt.hpp"
namespace Orbitons{
    class Entity3d {


    public:

        Entity3d();
        virtual ~Entity3d(){};

        size_t m_uuid;
        std::string m_name;
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
        glm::mat4 transforms;


        Ref<Entity3d> m_parent;
        void applyTransforms();

        void setScale(glm::vec3 _scale); 
        void setPosition(glm::vec3 _pos); 
        void setRotation(glm::vec3 _rot); 

    private:
        entt::entity m_entityHandle;
    };
}
#endif /* ENTITY_3D_H */