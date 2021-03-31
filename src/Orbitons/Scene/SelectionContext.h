#ifndef SELECTION_CONTEXT_H
#define SELECTION_CONTEXT_H

#include "core.h"
#include "entt/entt.hpp"
#include "Entity.h"
namespace Orbitons
{

    class SelectionContext
    {
    public:
        Entity m_selectedEntity;

        static SelectionContext &getInstance()
        {
            static SelectionContext s_instance;

            return s_instance;
        }

        void setSelectedEntity(Entity entity)
        {
            m_selectedEntity = entity;
        }

        Entity getSelectedEntity()
        {
            return m_selectedEntity;
        }

    private:
        SelectionContext() {}
    };
} // namespace Orbitons
#endif /* SELECTION_CONTEXT_H */