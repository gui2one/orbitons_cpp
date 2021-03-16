#ifndef CAMERA_CONTROLS_H
#define CAMERA_CONTROLS_H

#include "core.h"
#include "Core/Camera.h"

#include "Events/KeyboardEvent.h"
#include "Events/MouseEvent.h"


namespace Orbitons{

class CameraControls{
public: 

    CameraControls();
    CameraControls(Ref<Camera> camera);

    void setCamera(Ref<Camera>& camera){ m_camera = camera; }
    void update(float detla_time);

    void setEventCallback(std::function<void(Event&)> fn){ m_EventCallback = fn; }
    bool onKeyPressEvent(KeyPressEvent& e);
    bool onEvent(Event& e);
private:

    Ref<Camera> m_camera;

    std::function<void(Event&)> m_EventCallback;

};
}
#endif /* CAMERA_CONTROLS_H */