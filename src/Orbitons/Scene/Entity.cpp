#include "Entity.h"


namespace Orbitons
{
    Entity::Entity(entt::entity entityHandle, Scene* scene)
    :m_entityHandle(entityHandle), m_scene(scene)
    {

    }
} // namespace Orbitons
