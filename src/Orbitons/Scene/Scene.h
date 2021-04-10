#ifndef SCENE_H
#define SCENE_H

#include "core.h"
#include "pch.h"
#include "Core/Entity3d.h"
#include "Core/Mesh.h"
#include "Core/MeshUtils.h"
#include "Core/Camera.h"
#include "Renderer/Skybox.h"

#include "Scene/Components.h"
#include "entt/entt.hpp"

namespace Orbitons
{
    // forward declaration ... why ?!!
    class Entity;

    class Scene
    {

    public:
        Ref<Camera> m_activeCamera = nullptr;
        Ref<MaterialItem> m_defaultMaterialItem;
        std::vector<Ref<Entity3d>> objects;
        Ref<Skybox> skybox;

    public:
        void init();
        void add(Ref<Entity3d> entity);

        Entity createEntity(const std::string &name = std::string());
        void destroyEntity(entt::entity entity);

    private:
        entt::registry m_registry;

        friend class Entity;
        friend class UI;
        friend class Window;
        friend class Serializer;
    };
};     // end namespace
#endif /* SCENE_H */