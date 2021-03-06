
// #define GLEW_DLL
#include "glad/glad.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"


#include <stb_image.h>


#include "pch.h"
#include "core.h"

#include "orbital_body.h"


#include "core/MeshUtils.h"
#include "core/Material.h"
#include "core/Object3d.h"
#include "core/Timer.h"
#include "core/Camera.h"
#include "core/ObjectLoader.h"


#include "core/Scene.h"
#include "imgui/UI.h"

#include "Application.h"

#include "opengl_debug.h"

using  Orbitons::OrbitalBody;
using Orbitons::Ref;

ObjLoader loader;
Ref<Camera> camera;
Orbitons::Scene scene;

UI ui;

Ref<Object3d> dragon;
Ref<Object3d> plane;

Application app;

int width, height;


void createObjects(){
    dragon = std::make_shared<Object3d>();
    dragon->m_mesh = loader.assimp_load("../../resources/objects/dragon_full.glb");
    dragon->buildVBO();
    dragon->setScale(glm::vec3(10.f));
    dragon->setPosition(glm::vec3(0.f, 0.0f, 0.f));
    app.m_scene.add(dragon);


    plane = std::make_shared<Object3d>();
    plane->m_mesh = MeshUtils::makeGrid(10.f, 10.f, 2, 2);
    MeshUtils::rotateX(plane->m_mesh, PI / 2.0f);
    MeshUtils::computeNormals(plane->m_mesh);
    plane->buildVBO();
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



int main(){
  

    GLCall(glEnable(GL_DEPTH_TEST));
    float angle = 0.0f;
    float screen_ratio = (float)width / height;

    Timer timer;

    camera = std::make_shared<Camera>(glm::radians(45.0f),screen_ratio);
    camera->position.x = 5.0f;
    camera->position.y = 1.0f;
    camera->position.z = 0.f;
    camera->target_position.y = 0.05f;
    glm::vec3 up_vector = glm::vec3(0.0f, 1.0f, 0.0f);

    // app.scene.add(camera);

    createObjects();

    while(!app.m_window->shouldClose())
    {
        app.m_window->refresh(app.m_scene, camera, app.m_timer);
    }





    // glEnable(GL_DEPTH_TEST);
    
    // bool show_demo_window = true;
    
    // /* Loop until the user closes the window */
    // while (!glfwWindowShouldClose(window))
    // {




    //     timer.update();
	
    //     glfwGetFramebufferSize(window, &width, &height);
    //     glViewport(0,0,width, height);
    //     camera.setScreenRatio((float)width / (float)height);
    //     glm::mat4 view = glm::mat4(1.0f);

    //     float radius = 5.0f;
    //     float speed = 0.3f;
    //     angle += timer.getDeltaTime() * speed;
  
    //     view *= glm::lookAt(
    //         camera.position,
    //         camera.target_position,
    //         glm::normalize(up_vector)
    //     );

    //     glm::mat4 model = dragon->transforms;
    //     // model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.f, 1.f, 0.f));
    //     model = glm::rotate(model, angle, up_vector);

    //     glm::vec3 lightPos = glm::vec3(0.f, 2.f, 0.f);
    //     // wipe the drawing surface clear
    //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    //     Ref<Material> dragon_mat = dragon->m_material;
    //     glUniform3fv(glGetUniformLocation(dragon_mat->getShader()->m_id,"u_lightPos"), 1 , glm::value_ptr(lightPos));
    //     glUniform3fv(glGetUniformLocation(dragon_mat->getShader()->m_id,"u_cameraPos"), 1 , glm::value_ptr(camera.position));

    //     glUniformMatrix4fv(glGetUniformLocation(dragon_mat->getShader()->m_id,"u_model"), 1, GL_FALSE,glm::value_ptr(model));
        
    //     glUniformMatrix4fv(glGetUniformLocation(dragon_mat->getShader()->m_id, "u_projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
    //     glUniformMatrix4fv(glGetUniformLocation(dragon_mat->getShader()->m_id, "u_view"), 1, GL_FALSE, glm::value_ptr(view));
    //     // glBindVertexArray(dragon->vao);
    //     dragon->draw();

    //     ui.render();

    //     // update other events like input handling 
    //     glfwPollEvents();
    //     // put the stuff we've been drawing onto the display
    //     glfwSwapBuffers(window);
    // }

    glfwTerminate();


    return 0;
}