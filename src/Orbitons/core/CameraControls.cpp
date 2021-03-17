#include "CameraControls.h"
#include "Input.h"
#include <glm/glm.hpp>
namespace Orbitons{

    CameraControls::CameraControls()
        :   m_camera(nullptr), 
            m_uvPos(glm::vec2(PI*0.9f,PI/2.2f)), 
            m_radius(5.0f),
            m_cursorDelta(glm::vec2(0.f)),
            m_cursorOldPos(glm::vec2(0.f))
    {


    }

    CameraControls::CameraControls(Ref<Camera> camera)
        :   m_camera(camera), 
            m_uvPos(glm::vec2(PI*0.9f,PI/2.2f)), 
            m_radius(5.0f),
            m_cursorDelta(glm::vec2(0.f)),
            m_cursorOldPos(glm::vec2(0.f))
    {
        
    }
    void CameraControls::update(float delta_time){

        if( Input::isKeyPressed(GLFW_KEY_RIGHT)){
            m_uvPos.x -= 1.0f * delta_time;
        }
        if(Input::isKeyPressed(GLFW_KEY_LEFT)){
            m_uvPos.x += 1.0f * delta_time;
        }
        if(Input::isKeyPressed(GLFW_KEY_DOWN)){
            m_uvPos.y += 1.0f * delta_time;
        }
        if(Input::isKeyPressed(GLFW_KEY_UP)){
            m_uvPos.y -= 1.0f * delta_time;
        }

        if( Input::isKeyPressed(GLFW_KEY_LEFT_ALT) && Input::isMouseButtonClicked(0)){

            m_cursorDelta = Input::getMousePos() - m_cursorOldPos;

            m_uvPos += glm::vec2(m_cursorDelta.x * delta_time, m_cursorDelta.y * -delta_time);
        }
        
        m_camera->position = fromPolar(m_uvPos);
        m_cursorOldPos = Input::getMousePos();
    }

    glm::vec3 CameraControls::fromPolar(glm::vec2 uv_pos){
        glm::vec3 result;

      
        result.x = m_radius * sin(uv_pos.y)*cos(uv_pos.x);
        result.y = m_radius * cos(uv_pos.y);
        result.z = m_radius * sin(uv_pos.y)*sin(uv_pos.x);

        return result;
    }
    bool CameraControls::onKeyPressEvent(KeyPressEvent& e){

        // Input::isKeyPressed(e.m_Keycode);


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

    bool CameraControls::onMouseScrollEvent(MouseScrollEvent& e){
        m_radius *= 1.0f + (float)e.m_yoffset * -0.2f;
        return false;
    }
    bool CameraControls::onEvent(Event& e){
        
        // printf("CameraControls onEvent ...\n");
        Dispatcher dispatcher(e);
        dispatcher.dispatch<KeyPressEvent>(BIND_EVENT_FUNCTION(CameraControls::onKeyPressEvent));
        dispatcher.dispatch<MouseScrollEvent>(BIND_EVENT_FUNCTION(CameraControls::onMouseScrollEvent));

        return true;
    }
}