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
        uint64_t m_selectedEntityID;

        static SelectionContext &getInstance()
        {
            static SelectionContext s_instance;

            return s_instance;
        }

        void setSelectedEntity(uint64_t entity_id)
        {
            m_selectedEntityID = entity_id;
        }

    private:
        SelectionContext() {}
    };
} // namespace Orbitons
#endif /* SELECTION_CONTEXT_H */