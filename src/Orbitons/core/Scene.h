#ifndef SCENE_H
#define SCENE_H

#include "core.h"
#include "pch.h"
#include "Entity3d.h"
#include "Camera.h"
#include "Renderer/Skybox.h"

namespace Orbitons
{

    class Scene{

    public:
        Ref<Camera> m_activeCamera = nullptr;
    public:
        
        void init();
        void add(Ref<Entity3d> entity);
        
        
        std::vector<Ref<Entity3d>> objects;
        Ref<Skybox> skybox;

    private:

    };
}; // end namespace
#endif /* SCENE_H */