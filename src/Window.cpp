#include "Window.h"

#include "opengl_debug.h"

Window::Window(){
    int width = 1280;
    int height = 720;


    if (!glfwInit())
        glfwTerminate();

    win = glfwCreateWindow(width, height, "Orbitons -- Renderer !!!", NULL, NULL);
    if (!win)
    {
        glfwTerminate();
        
    }

    // glfwSetKeyCallback(win, key_callback);


    glfwMakeContextCurrent(win);



    

    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    if( !status){
        printf("Problem with glad\n");
        glfwTerminate();
    }

    
    printf("GL version: %s\n", glGetString(GL_VERSION));
    printf("GL shading language version: %s\n", 
    glGetString(GL_SHADING_LANGUAGE_VERSION));

    m_ui.init(win);
    glfwSwapInterval(1);
}

void Window::refresh(Orbitons::Scene& scene, Orbitons::Ref<Camera> camera, Timer& timer){

        
        glEnable(GL_DEPTH_TEST);
        // timer.update();
        int width, height;
        glfwGetFramebufferSize(win, &width, &height);
        glViewport(0,0,width, height);
        camera->setScreenRatio((float)width / (float)height);
        glm::mat4 view = glm::mat4(1.0f);

        float radius = 5.0f;
        float speed = 0.2f;
        float angle = timer.getElapsedTime() * speed;
        glm::vec3 up_vector(0.f,1.f,0.f);
        view *= glm::lookAt(
            camera->position,
            camera->target_position,
            glm::normalize(up_vector)
        );

        glClearColor(1.0f, 0.f, 0.f,1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.skybox.draw(camera.get());


        for(auto current : scene.objects){


            Orbitons::Ref<Object3d> object = std::static_pointer_cast<Object3d>(current);
            Orbitons::Ref<Material> material = object->m_material;
            material->useProgram();
            glm::mat4 model(1.f);
            model = current->transforms * model;


            glm::vec3 lightPos = glm::vec3(0.f, 2.f, -2.f);

            

           
            glUniform3fv(glGetUniformLocation(material->getShaderID(),"u_lightPos"), 1 , glm::value_ptr(lightPos));

            glUniform3fv(glGetUniformLocation(material->getShaderID(),"u_cameraPos"), 1 , glm::value_ptr(camera->position));


            glUniformMatrix4fv(glGetUniformLocation(material->getShaderID(),"u_model"), 1, GL_FALSE,glm::value_ptr(model));
            glUniformMatrix4fv(glGetUniformLocation(material->getShaderID(), "u_projection"), 1, GL_FALSE, glm::value_ptr(camera->projection));
            glUniformMatrix4fv(glGetUniformLocation(material->getShaderID(), "u_view"), 1, GL_FALSE, glm::value_ptr(view));
            // glBindVertexArray(object->vao);
            object->draw();

            glUseProgram(0);

            
        }
      

        m_ui.render();


        // put the stuff we've been drawing onto the display
        glfwSwapBuffers(win);
        // update other events like input handling 
        glfwPollEvents();

}
bool Window::shouldClose(){
    return glfwWindowShouldClose(win);
}