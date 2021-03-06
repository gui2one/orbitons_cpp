#include "Scene.h"

namespace Orbitons{

    void Scene::add(Ref<Entity3d> entity)
    {
        objects.push_back(entity);
    }
};