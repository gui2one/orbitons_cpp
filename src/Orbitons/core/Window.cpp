#include "Window.h"


#include "Events/KeyboardEvent.h"
#include "Events/MouseEvent.h"
#include "Events/WindowEvent.h"
namespace Orbitons{
    Window::Window(){
        int width = 1280;
        int height = 720;


        if (!glfwInit()){
            ORBITONS_ASSERT(false, "GLFW Error \n");
            glfwTerminate();
        }

        glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
        win = glfwCreateWindow(width, height, "Orbitons -- v0.01 alpha", NULL, NULL);
        if (!win)
        {
            ORBITONS_ASSERT(false, "GLFW Window Error\n");
            glfwTerminate();
            
        }

        glfwSetWindowUserPointer(win, this);
        
        
        glfwMakeContextCurrent(win);



        // set GLFW window icon
        GLFWimage icons[1]; 
        icons[0].pixels = stbi_load("resources/icon.png", &icons[0].width, &icons[0].height, 0, 4); //rgba channels 
        glfwSetWindowIcon(win, 1, icons); 
        stbi_image_free(icons[0].pixels);
        /////////////////////


                
        m_context = GraphicContext::create(win);
        m_context->init();

        m_ui.setContext(*m_context);
        m_frameBuffer = FrameBuffer::create();        

        m_ui.init(win);
        glfwSwapInterval(1);

        /* set callbacks */
        glfwSetKeyCallback(win, [](GLFWwindow* window, int key, int scancode, int action, int mods){
            
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            if( action == GLFW_PRESS){
                KeyPressEvent event(key, 0);
                data.eventCallback(event);
                // static_cast<Window*>(glfwGetWindowUserPointer(window))->onKeyPressEvent(event);
            }
        });

        glfwSetMouseButtonCallback(win, [](GLFWwindow* window, int button, int action, int mods){

        });

        glfwSetWindowSizeCallback(win, [](GLFWwindow* window, int width, int height){

        });

        glfwSetWindowCloseCallback(win, [](GLFWwindow* window){

        });


    }

    void Window::refresh(Scene& scene, Timer& timer){


            glEnable(GL_DEPTH_TEST);
            // timer.update();
            int width, height;
            ImVec2 viewportSize = m_ui.getViewportSize();
            width = viewportSize.x;
            height = viewportSize.y;

            if( m_ui.getViewportSizeChanged()){
                
                m_frameBuffer->invalidate(width,height);
            }            

            // glfwGetFramebufferSize(win, &width, &height);
            glViewport(0,0,width, height);
            scene.m_activeCamera->setScreenRatio((float)width / (float)height);
            glm::mat4 view = glm::mat4(1.0f);

            float radius = 5.0f;
            float speed = 0.2f;
            float angle = timer.getElapsedTime() * speed;
            glm::vec3 up_vector(0.f,1.f,0.f);
            view *= glm::lookAt(
                scene.m_activeCamera->position,
                scene.m_activeCamera->target_position,
                glm::normalize(up_vector)
            );


            m_frameBuffer->bind();


            glClearColor(1.0f, 0.f, 0.f,1.f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            scene.skybox->draw(scene.m_activeCamera.get());

            glm::vec3 lightPos = glm::vec3(0.f, 2.f, 2.f);
            for(auto current : scene.objects){

                Ref<Object3d> object = std::static_pointer_cast<Object3d>(current);
                Ref<Material> material = object->m_material;
                material->useProgram();
                glm::mat4 model(1.f);
                model = current->transforms * model;
            
                glUniform3fv(glGetUniformLocation(material->getShaderID(),"u_lightPos"), 1 , glm::value_ptr(lightPos));
                glUniform3fv(glGetUniformLocation(material->getShaderID(),"u_cameraPos"), 1 , glm::value_ptr(scene.m_activeCamera->position));

                glUniformMatrix4fv(glGetUniformLocation(material->getShaderID(),"u_model"), 1, GL_FALSE,glm::value_ptr(model));
                glUniformMatrix4fv(glGetUniformLocation(material->getShaderID(), "u_projection"), 1, GL_FALSE, glm::value_ptr(scene.m_activeCamera->projection));
                glUniformMatrix4fv(glGetUniformLocation(material->getShaderID(), "u_view"), 1, GL_FALSE, glm::value_ptr(view));
    
                object->draw();

                glUseProgram(0);

                
            }
        
            m_frameBuffer->unbind();
            m_ui.render(m_frameBuffer);


            // put the stuff we've been drawing onto the display
            
            m_context->swapBuffers();
            // update other events like input handling 
            glfwPollEvents();

    }

    bool Window::onKeyPressEvent(Event& e){


        // printf("KeyPressEvent from Window\n");
        return false;
    }

    bool Window::onEvent(Event& e)
    {
        Dispatcher dispatcher(e);

        dispatcher.dispatch<KeyPressEvent>(BIND_EVENT_FUNCTION(Window::onKeyPressEvent));
        return true;
    }

    bool Window::shouldClose(){

        return glfwWindowShouldClose(win);
    }
}