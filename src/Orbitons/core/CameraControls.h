#ifndef CAMERA_CONTROLS_H
#define CAMERA_CONTROLS_H

#include "core.h"
#include "core/Camera.h"
namespace Orbitons{

class CameraControls{
public: 
    CameraControls();
    CameraControls(Ref<Camera> camera);

    void update(float detla_time);
private:

};
}
#endif /* CAMERA_CONTROLS_H */