
// #define GLEW_DLL

#include "pch.h"
#include "core.h"

#include "orbital_body.h"


#include "core/MeshUtils.h"
#include "core/Material.h"
#include "core/Object3d.h"
#include "core/Timer.h"
#include "core/Camera.h"
#include "core/ObjectLoader.h"

using  Orbitons::OrbitalBody;
using Orbitons::Ref;

ObjLoader loader;
Camera camera;
int curMaterialID = 0;
std::vector< Ref<Material> > materials;

std::vector< Ref<Object3d> > scene_objects;
Ref<Object3d> dragon_object;
Ref<Object3d> plane_object;

int width, height;

// scene_objects.push_back(dragon_object);

void createObjects(){
    dragon_object = std::make_shared<Object3d>();
    dragon_object->m_mesh = loader.assimp_load("../../resources/objects/dragon_full.ply");
    dragon_object->buildVBO();
    dragon_object->setScale(glm::vec3(0.2f));
    scene_objects.push_back(dragon_object);

    plane_object = std::make_shared<Object3d>();
    scene_objects.push_back(plane_object);
}

void create_materials(){

    std::shared_ptr<PhongMaterial> phong_material = std::make_shared<PhongMaterial>();
    std::shared_ptr<UnlitMaterial> unlit_material = std::make_shared<UnlitMaterial>();
    phong_material->diffuseColor = glm::vec3(1.0f, 0.1f, 0.1f);
    unlit_material->color = glm::vec3(0.f, 0.5f, 0.f);
    
    materials.push_back(phong_material);
    materials.push_back(unlit_material);
}

void cycle_materials(){
    if(curMaterialID >= materials.size() -1){
        curMaterialID = 0;
    }else{
        curMaterialID ++;
    }
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
    width = 1920;
    height = 1000;
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(width, height, "Orbitons -- Renderer", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);



    glfwMakeContextCurrent(window);

    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    if( !status){
        printf("Problem with glad\n");
        return -1;
    }



    printf("GL version: %s\n", glGetString(GL_VERSION));
    printf("GL shading language version: %s\n", 
    glGetString(GL_SHADING_LANGUAGE_VERSION));
    glfwSwapInterval(1);

    // unlit_material->initShader();
    createObjects();
    create_materials();

    float angle = 0.0f;
    float screen_ratio = (float)width / height;

    Timer timer;

    camera = Camera(glm::radians(60.0f),screen_ratio);
    camera.position.x = 0.14f;
    camera.position.y = 0.1f;
    camera.position.z = 0.f;
    camera.target_position.y = 0.05f;
    glm::vec3 up_vector = glm::vec3(0.0f, 1.0f, 0.0f);




    glEnable(GL_DEPTH_TEST);
    

    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        timer.update();
	
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0,0,width, height);
        camera.setScreenRatio((float)width / (float)height);
        glm::mat4 view = glm::mat4(1.0f);

        float radius = 5.0f;
        float speed = 0.3f;
        angle += timer.getDeltaTime() * speed;
  
        view *= glm::lookAt(
            camera.position,
            camera.target_position,
            glm::normalize(up_vector)
        );

        glm::mat4 model = dragon_object->transforms;
        // model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.f, 1.f, 0.f));
        model = glm::rotate(model, angle, up_vector);

        glm::vec3 lightPos = glm::vec3(0.f, 2.f, 0.f);
        // wipe the drawing surface clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        Ref<Material> dragon_mat = dragon_object->m_material;
        glUniform3fv(glGetUniformLocation(dragon_mat->getShader()->m_id,"u_lightPos"), 1 , glm::value_ptr(lightPos));
        glUniform3fv(glGetUniformLocation(dragon_mat->getShader()->m_id,"u_cameraPos"), 1 , glm::value_ptr(camera.position));

        glUniformMatrix4fv(glGetUniformLocation(dragon_mat->getShader()->m_id,"u_model"), 1, GL_FALSE,glm::value_ptr(model));
        
        glUniformMatrix4fv(glGetUniformLocation(dragon_mat->getShader()->m_id, "u_projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
        glUniformMatrix4fv(glGetUniformLocation(dragon_mat->getShader()->m_id, "u_view"), 1, GL_FALSE, glm::value_ptr(view));
        // glBindVertexArray(dragon_object->vao);
        dragon_object->draw();
        // update other events like input handling 
        glfwPollEvents();
        // put the stuff we've been drawing onto the display
        glfwSwapBuffers(window);
    }

    glfwTerminate();


    return 0;
}