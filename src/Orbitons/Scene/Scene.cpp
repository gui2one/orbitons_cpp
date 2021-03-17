#include "Scene.h"

#include "Entity.h"
#include "Components.h"
namespace Orbitons
{

    void Scene::init()
    {
        skybox = Skybox::create();
        skybox->init();

        if (m_activeCamera == nullptr)
        {
            m_activeCamera = MakeRef<Camera>(glm::radians(65.0f), 16.0f / 9.0f);
            add(m_activeCamera);
        }
    }

    void Scene::add(Ref<Entity3d> entity)
    {
        objects.push_back(entity);
    }

    Entity Scene::createEntity(const std::string &name)
    {
        Entity entity(m_registry.create(), this);

        m_registry.emplace<TagComponent>(entity, name);
        m_registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

        Mesh mesh = MeshUtils::makeQuad();
        m_registry.emplace<MeshComponent>(entity, mesh);

        return entity;
    }

    void Scene::destroyEntity(entt::entity entity)
    {
        m_registry.destroy(entity);
    }
};