#ifndef ENTITY_H
#define ENTITY_H


#include "Scene.h"

namespace Orbitons
{
    class Entity{
    public:
        Entity() = default;
        Entity(entt::entity entityHandle, Scene* scene);
        Entity(const Entity& other) = default;

        entt::entity const getHandle() const { return m_entityHandle; }
        entt::entity getHandle() { return m_entityHandle; }
    private:
        entt::entity m_entityHandle{ entt::null };
        Scene* m_scene;

    };
} // namespace Orbitons
#endif /* ENTITY_H */