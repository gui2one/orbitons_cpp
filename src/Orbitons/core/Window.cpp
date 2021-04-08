#include "Window.h"

#include "Events/KeyboardEvent.h"
#include "Events/MouseEvent.h"
#include "Events/WindowEvent.h"

#include "Scene/Entity.h"
#include "entt/entt.hpp"
namespace Orbitons
{

    Window::Window()
    {
        int width = 1280;
        int height = 720;

        if (!glfwInit())
        {
            ORBITONS_ASSERT(false, "GLFW Error \n");
            glfwTerminate();
        }

        glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);

        m_window = glfwCreateWindow(width, height, "Orbitons -- v0.01 alpha", NULL, NULL);
        if (!m_window)
        {
            ORBITONS_ASSERT(false, "GLFW Window Error\n");
            glfwTerminate();
        }

        m_data.Title = "Hello";

        // set GLFW window icon
        GLFWimage icons[1];
        icons[0].pixels = stbi_load("resources/icon.png", &icons[0].width, &icons[0].height, 0, 4); //rgba channels
        glfwSetWindowIcon(m_window, 1, icons);
        stbi_image_free(icons[0].pixels);
        /////////////////////

        m_context = GraphicContext::create(m_window);
        m_context->init();

        m_ui.setContext(*m_context);
        m_frameBuffer = FrameBuffer::create();
        m_scene.init();

        m_ui.init(m_window);
        m_ui.setScene(m_scene);

        // m_scene.createEntity("first");

        glfwSetWindowUserPointer(m_window, &m_data);
        glfwSwapInterval(1);

        /* set callbacks */
        glfwSetKeyCallback(m_window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
            ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS:
            {
                KeyPressEvent event(key, scancode, 0);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleaseEvent event(key, scancode);
                data.EventCallback(event);
                break;
            }
            case GLFW_REPEAT:
            {
                KeyPressEvent event(key, scancode, 1);
                data.EventCallback(event);
                break;
            }
            };
        });

        glfwSetWindowSizeCallback(m_window, [](GLFWwindow *window, int width, int height) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_window, [](GLFWwindow *window, double x_pos, double y_pos) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            MouseMoveEvent event(x_pos, y_pos);
            data.EventCallback(event);
        });

        glfwSetScrollCallback(m_window, [](GLFWwindow *window, double xoffset, double yoffset) {
            ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

            MouseScrollEvent event(xoffset, yoffset);
            data.EventCallback(event);
        });
    }

    void Window::refresh(Timer &timer)
    {
        int width, height;
        ImVec2 viewportSize = m_ui.getViewportSize();
        width = viewportSize.x;
        height = viewportSize.y;

        // glViewport(0, 0, width, height);
        m_scene.m_activeCamera->setScreenRatio((float)width / (float)height);
        if (m_ui.getViewportSizeChanged())
        {
            m_frameBuffer->invalidate(width, height);
        }
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        m_controls.setCamera(m_scene.m_activeCamera);

        m_controls.activated = m_ui.isMouseOverViewport;
        m_controls.update(timer.getDeltaTime());

        glm::mat4 view = glm::mat4(1.0f);

        glm::vec3 up_vector(0.f, 1.f, 0.f);
        view *= glm::lookAt(
            m_scene.m_activeCamera->position,
            m_scene.m_activeCamera->target_position,
            glm::normalize(up_vector));

        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_frameBuffer->bind();

        // glClearColor(1.0f, 0.f, 0.f,1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_scene.skybox->draw(m_scene.m_activeCamera.get());

        glm::vec3 lightPos = glm::vec3(2.f, 2.f, 2.f);

        auto meshes = m_scene.m_registry.view<UUIDComponent, MeshComponent, TagComponent, TransformComponent>();
        // printf("meshes size : %d\n", meshes.size_hint);
        for (auto entity : meshes)
        {

            auto [uuid, mesh, tag, transform] = meshes.get<UUIDComponent, MeshComponent, TagComponent, TransformComponent>(entity);

            mesh.material->useProgram();
            glm::mat4 model(1.f);

            model = transform.getTransforms() * model;

            // printf("material id --> %d\n", mesh.material->getShaderID());

            glUniform3fv(glGetUniformLocation(mesh.material->getShaderID(), "u_lightPos"), 1, glm::value_ptr(lightPos));
            glUniform3fv(glGetUniformLocation(mesh.material->getShaderID(), "u_cameraPos"), 1, glm::value_ptr(m_scene.m_activeCamera->position));

            glUniformMatrix4fv(glGetUniformLocation(mesh.material->getShaderID(), "u_model"), 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(glGetUniformLocation(mesh.material->getShaderID(), "u_projection"), 1, GL_FALSE, glm::value_ptr(m_scene.m_activeCamera->projection));
            glUniformMatrix4fv(glGetUniformLocation(mesh.material->getShaderID(), "u_view"), 1, GL_FALSE, glm::value_ptr(view));

            mesh.material->useProgram();

            if (mesh.mesh_item != nullptr)
                mesh.mesh_item->mesh_object.draw();
            glUseProgram(0);
        }

        m_frameBuffer->unbind();
        m_ui.render(m_frameBuffer);

        glfwPollEvents();
        m_context->swapBuffers();
    }

    bool Window::onKeyPressEvent(Event &e)
    {

        KeyPressEvent &event = static_cast<KeyPressEvent &>(e);
        if (event.m_Keycode == 57) /*space bar*/
        {
            printf("space bar pressed\n");
            return true;
        }
        return true;
    }

    bool Window::onEvent(Event &e)
    {

        // m_controls.onEvent(e);

        Dispatcher dispatcher(e);
        dispatcher.dispatch<KeyPressEvent>(BIND_EVENT_FUNCTION(Window::onKeyPressEvent));

        return true;
    }

    bool Window::shouldClose()
    {

        return glfwWindowShouldClose(m_window);
    }
}