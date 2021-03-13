
// #define GLEW_DLL
#include <windows.h>
#include "glad/glad.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"


#include <stb_image.h>


#include "pch.h"
#include "core.h"

#include "orbital_body.h"


#include "core/MeshUtils.h"
#include "Renderer/Material.h"
#include "core/Object3d.h"
#include "core/Timer.h"
#include "core/Camera.h"
#include "core/CameraControls.h"
#include "core/ObjectLoader.h"


#include "core/Scene.h"
#include "imgui/UI.h"

#include "Application.h"

#include "opengl_debug.h"
#include "Events/KeyboardEvent.h"


using namespace Orbitons;

ObjLoader loader;
Ref<Camera> camera;
Ref<CameraControls> controls;
Scene scene;

UI ui;

Ref<Object3d> dragon;
Ref<Object3d> plane;

Application app;


EventQueue * event_queue = EventQueue::getInstance();
int width, height;


void createObjects(){

    
    ORBITONS_ASSERT(true, "Assertion test only ....");
    dragon = MakeRef<Object3d>();
    dragon->m_mesh = loader.assimp_load("../../resources/objects/dragon_full.glb");
    dragon->buildBuffers();
    dragon->setScale(glm::vec3(10.f));
    dragon->setPosition(glm::vec3(0.f, 0.0f, 0.f));

    std::static_pointer_cast<PhongMaterial>(dragon->m_material)->setDiffuseColor(glm::vec3(1.f));

    app.m_scene.add(dragon);


    plane = MakeRef<Object3d>();
    plane->m_mesh = MeshUtils::makeGrid(1.f, 1.f, 2, 2);
    MeshUtils::rotateX(plane->m_mesh, PI / 2.0f);
    MeshUtils::computeNormals(plane->m_mesh);
    plane->buildBuffers();
    plane->setScale(glm::vec3(1.0f));

    app.m_scene.add(plane);
}

int main(int argc, char** argv){


    Ref<Event> event = MakeRef<KeyPressEvent>(42, 0);

    event->m_Callback = [](){
        printf("custom event \n");
    };
    event_queue->push(event);

    
    glEnable(GL_DEPTH_TEST);
    float screen_ratio = (float)width / height;

    float angle = 0.0f;
    camera = MakeRef<Camera>(glm::radians(65.0f),screen_ratio);

    controls = MakeRef<CameraControls>(camera);
    createObjects();

    float rotation_speed = 0.05f;
    float radius  = 3.0f;
    while(!app.m_window->shouldClose())
    {
        event_queue->process();
        float delta_time = app.m_timer.getDeltaTime();
        app.m_timer.update();
        controls->update(delta_time);

        angle = app.m_timer.getElapsedTime();

        glm::vec3 up_vector = glm::vec3(0.0f, 1.0f, 0.0f);        


        app.m_window->refresh(app.m_scene, camera, app.m_timer);
    }
  
    glfwTerminate();

    exit(EXIT_SUCCESS);
    printf("Termination .....\n");
    return 0;
}