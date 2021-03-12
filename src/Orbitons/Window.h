#ifndef WINDOW_H
#define WINDOW_H

#include "pch.h"
#include "core/Scene.h"
#include "core/Camera.h"
#include "core/Timer.h"
#include "core/Object3d.h"
#include "imgui/UI.h"


#include "Events/Event.h"
namespace Orbitons{

    class Window{
        
    public:
            
        GLFWwindow * win;
        UI m_ui;
        Orbitons::EventQueue m_EventQueue;

    public:
        Window();

        void refresh(Orbitons::Scene& scene, Orbitons::Ref<Camera> camera, Timer& timer);
        bool shouldClose();

        static void char_mods_callback(GLFWwindow* window, unsigned int key, int action);
        static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
        static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);	
        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


    private:

    };
}
#endif /* WINDOW_H */