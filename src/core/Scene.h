#ifndef SCENE_H
#define SCENE_H

#include "../pch.h"
#include "../core.h"
#include "Entity3d.h"

namespace Orbitons
{

    class Scene{
    public:
        std::vector<Ref<Entity3d>> objects;

        void add(Ref<Entity3d> entity);
    private:

    };
}; // end namespace
#endif /* SCENE_H */