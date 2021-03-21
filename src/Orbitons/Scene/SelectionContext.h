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
        entt::entity m_selectedEntity;

        static SelectionContext &getInstance()
        {
            static SelectionContext s_instance;

            return s_instance;
        }

        void setSelectedEntity(entt::entity entity)
        {
            m_selectedEntity = entity;
        }

    private:
        SelectionContext() {}
    };
} // namespace Orbitons
#endif /* SELECTION_CONTEXT_H */