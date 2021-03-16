#include "CameraControls.h"
#include "Input.h"

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

        Input::isKeyPressed(e.m_Keycode);
        // printf("scancode %d", e.m_Keycode);

        switch (e.m_Keycode)
        {
        case GLFW_KEY_W:
            m_camera->position.x -= 0.1f;
            break;
        case GLFW_KEY_A:
            m_camera->position.z += 0.1f;
            break;
        case GLFW_KEY_S:
            m_camera->position.x += 0.1f;
            break;    
        case GLFW_KEY_D:
            m_camera->position.z -= 0.1f;
            break;                       
                
        default:
            break;
        }
        return false;
    }
    bool CameraControls::onEvent(Event& e){
        
        // printf("CameraControls onEvent ...\n");
        Dispatcher dispatcher(e);
        dispatcher.dispatch<KeyPressEvent>(BIND_EVENT_FUNCTION(CameraControls::onKeyPressEvent));

        return true;
    }
}