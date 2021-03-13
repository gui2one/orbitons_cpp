#include "Scene.h"

namespace Orbitons{

    void Scene::init(){
        skybox = Skybox::create();
        skybox->init();

        if(m_activeCamera == nullptr){
            m_activeCamera = MakeRef<Camera>(glm::radians(65.0f),16.0f/9.0f);
        }
    }
    
    void Scene::add(Ref<Entity3d> entity)
    {
        objects.push_back(entity);
    }


};