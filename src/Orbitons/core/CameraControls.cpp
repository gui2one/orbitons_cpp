#include "CameraControls.h"

namespace Orbitons{

    CameraControls::CameraControls()
    :m_camera(nullptr)
    {
        printf("CameraControls constructor ...\n");
    }

    CameraControls::CameraControls(Ref<Camera> camera)
    :m_camera(camera)
    {
        
    }
    void CameraControls::update(float detla_time){

    }

    bool CameraControls::onKeyPressEvent(KeyPressEvent& e){

        // printf("scancode %d", e.m_Scancode);
        if( e.m_Scancode == 17){
            m_camera->position.x += 0.01f;
        }
        return false;
    }
    bool CameraControls::onEvent(Event& e){
        
        printf("CameraControls onEvent ...\n");
        Dispatcher dispatcher(e);
        dispatcher.dispatch<KeyPressEvent>(BIND_EVENT_FUNCTION(CameraControls::onKeyPressEvent));

        return true;
    }
}