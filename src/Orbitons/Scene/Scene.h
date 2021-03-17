#ifndef SCENE_H
#define SCENE_H

#include "core.h"
#include "pch.h"
#include "Core/Entity3d.h"
#include "Core/Camera.h"
#include "Renderer/Skybox.h"

#include "entt/entt.hpp"


namespace Orbitons
{
    // forward declaration ... why ?!! 
    class Entity;

    class Scene{

    public:
        Ref<Camera> m_activeCamera = nullptr;
    public:
        
        void init();
        void add(Ref<Entity3d> entity);
        
        Entity createEntity(const std::string& name = std::string());
        
        std::vector<Ref<Entity3d>> objects;
        Ref<Skybox> skybox;

    private:
        entt::registry m_registry;

        friend class Entity;
    };
}; // end namespace
#endif /* SCENE_H */