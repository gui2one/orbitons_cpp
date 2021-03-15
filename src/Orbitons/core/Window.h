#ifndef WINDOW_H
#define WINDOW_H
// #include "GLFW/glfw3.h"


#include "pch.h"
#include "Core/Scene.h"
#include "Core/Camera.h"
#include "Core/Timer.h"
#include "Core/Object3d.h"
#include "Imgui/UI.h"


#include "Events/Event.h"
#include "Renderer/FrameBuffer.h"

#include "Renderer/GraphicContext.h"
namespace Orbitons{

    class Window{
        
    public:
            
       
        UI m_ui;
        
    public:
        Window();

        void refresh(Orbitons::Scene& scene, Timer& timer);
        bool shouldClose();

        //static void char_mods_callback(GLFWwindow* window, unsigned int key, int action);
        //static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
        //static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);	
        //static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

        bool onKeyPressEvent(Event& e);
        bool onEvent(Event& e);
        void setEventCallback(std::function<void(Event&)> callback){ m_data.EventCallback = callback; }

        GLFWwindow* getNativeWindow() const  { return m_window;  }
        Ref<GraphicContext> getContext() const { return m_context;  }


    private:

        GLFWwindow* m_window;
        Ref<GraphicContext> m_context;
        std::function<void(Event&)> m_callback;
        Ref<FrameBuffer> m_frameBuffer;


        struct WindowData{
            
            std::string Title;
            unsigned int Width, Height;
            bool VSync;
            std::function<void(Event&)> EventCallback;

        };
    
        WindowData m_data;

    };
}
#endif /* WINDOW_H */