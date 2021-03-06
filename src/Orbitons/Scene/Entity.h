#ifndef ENTITY_H
#define ENTITY_H

#include "Components.h"
#include "Scene.h"

namespace Orbitons
{
    class Entity
    {

    public:
        Entity() = default;
        Entity(entt::entity entityHandle, Scene *scene);
        Entity(const Entity &other) = default;

        entt::entity const getHandle() const { return m_entityHandle; }
        entt::entity getHandle() { return m_entityHandle; }
        // std::string getUUID() { return m_uuid; }
        // void setUUID(std::string uuid) { m_uuid = uuid; }
        operator entt::entity() { return m_entityHandle; }

        template <typename T>
        T &getComponent()
        {
            ORBITONS_ASSERT(hasComponent<T>(), "the component does'nt exists on this entity");
            return m_scene->m_registry.get<T>(m_entityHandle);
        }

        template <typename T>
        bool hasComponent()
        {
            return m_scene->m_registry.has<T>(m_entityHandle);
        }

        template <typename T>
        void removeComponent()
        {
            m_scene->m_registry.remove<T>(m_entityHandle);
        }

        operator bool() const { return m_entityHandle != entt::null; }

    private:
        entt::entity m_entityHandle{entt::null};
        Scene *m_scene;
        // std::string m_uuid;
    };
} // namespace Orbitons
#endif /* ENTITY_H */