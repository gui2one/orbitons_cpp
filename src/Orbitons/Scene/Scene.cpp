#include "Scene.h"

#include "Entity.h"
#include "Components.h"

#include "Core/IDGenerator.h"
namespace Orbitons
{

    void Scene::init()
    {
        skybox = Skybox::create();
        skybox->init();

        if (m_activeCamera == nullptr)
        {
            m_activeCamera = MakeRef<Camera>(glm::radians(65.0f), 1.0f);
            add(m_activeCamera);
        }

        m_defaultMaterialItem = MakeRef<PhongMaterialItem>();
    }

    void Scene::add(Ref<Entity3d> entity)
    {
        objects.push_back(entity);
    }

    Entity Scene::createEntity(const std::string &name)
    {

        Entity entity(m_registry.create(), this);

        std::string uuid = IDGenerator::generateUUID();

        m_registry.emplace<UUIDComponent>(entity, uuid);
        m_registry.emplace<TagComponent>(entity, name);
        m_registry.emplace<TransformComponent>(entity, glm::vec3(0.f, 0.f, 0.f));

        m_registry.emplace<MeshComponent>(entity);

        return entity;
    }

    void Scene::destroyEntity(entt::entity entity)
    {
        m_registry.destroy(entity);
    }
};