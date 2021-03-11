
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
#include "core/ObjectLoader.h"


#include "core/Scene.h"
#include "imgui/UI.h"

#include "Application.h"

#include "opengl_debug.h"

using Orbitons::OrbitalBody;
using Orbitons::Ref;
using Orbitons::MakeRef;

ObjLoader loader;
Ref<Camera> camera;
Orbitons::Scene scene;

UI ui;

Ref<Object3d> dragon;
Ref<Object3d> plane;

Application app;



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
    // plane->setRotation(glm::vec3(90.0f, 0.f, 0.f));
    app.m_scene.add(plane);
}


void cycle_materials(){
    printf("cycle materials\n");

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // printf("Key -> %d\n", key);
    // printf("Scancode -> %d\n", scancode);
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {

    }else if( scancode == 39 /* m key */&& action == GLFW_PRESS){
        cycle_materials();
    }
}



int main(int argc, char** argv){


    glEnable(GL_DEPTH_TEST);
    float screen_ratio = (float)width / height;

    float angle = 0.0f;
    camera = Orbitons::MakeRef<Camera>(glm::radians(65.0f),screen_ratio);

    createObjects();

    float rotation_speed = 0.05f;
    float radius  = 3.0f;
    while(!app.m_window->shouldClose())
    {
        app.m_timer.update();

        angle = app.m_timer.getElapsedTime();
        camera->position.x = sinf(angle * rotation_speed) * radius;
        camera->position.y = 1.0f;
        camera->position.z = cosf(angle * rotation_speed) * radius;
        camera->target_position.y = 0.05f;
        glm::vec3 up_vector = glm::vec3(0.0f, 1.0f, 0.0f);        


        app.m_window->refresh(app.m_scene, camera, app.m_timer);
    }

    

    // // Cleanup
    // ImGui_ImplOpenGL3_Shutdown();
    // ImGui_ImplGlfw_Shutdown();
    // ImGui::DestroyContext();

    // glfwDestroyWindow(app.m_window->win);    
    glfwTerminate();

    exit(EXIT_SUCCESS);
    printf("Termination .....\n");
    return 0;
}