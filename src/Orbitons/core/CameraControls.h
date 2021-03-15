#ifndef CAMERA_CONTROLS_H
#define CAMERA_CONTROLS_H

#include "core.h"
#include "Core/Camera.h"
namespace Orbitons{

class CameraControls{
public: 
    /**
     *  NOT implemented !
     */
    CameraControls();
    CameraControls(Ref<Camera> camera);

    void update(float detla_time);
private:

    Ref<Camera> m_camera;

};
}
#endif /* CAMERA_CONTROLS_H */