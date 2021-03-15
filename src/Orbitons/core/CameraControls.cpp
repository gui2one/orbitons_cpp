#include "CameraControls.h"

namespace Orbitons{

    CameraControls::CameraControls()
    :m_camera(nullptr)
    {
        
    }

    CameraControls::CameraControls(Ref<Camera> camera)
    :m_camera(camera)
    {
        
    }
    void CameraControls::update(float detla_time){

    }
}