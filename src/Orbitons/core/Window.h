#ifndef WINDOW_H
#define WINDOW_H
// #include "GLFW/glfw3.h"

#include "pch.h"
#include "Scene/Scene.h"
#include "Core/Camera.h"
#include "Core/CameraControls.h"
#include "Core/Timer.h"
#include "Core/Object3d.h"
#include "Imgui/UI.h"

#include "Events/Event.h"
#include "Renderer/FrameBuffer.h"

#include "Renderer/GraphicContext.h"
namespace Orbitons
{

    class Window
    {

    public:
        CameraControls m_controls;
        Scene m_scene;

        UI m_ui;

    public:
        Window();

        void refresh(Timer &timer);
        bool shouldClose();

        bool onKeyPressEvent(Event &e);
        bool onEvent(Event &e);
        void setEventCallback(std::function<void(Event &)> callback) { m_data.EventCallback = callback; }

        GLFWwindow *getNativeWindow() const { return m_window; }
        // GLFWwindow* getNativeWindow()  { return m_window;  }
        Ref<GraphicContext> getContext() const { return m_context; }

    private:
        GLFWwindow *m_window;
        Ref<GraphicContext> m_context;
        std::function<void(Event &)> m_callback;
        Ref<FrameBuffer> m_frameBuffer;

        struct WindowData
        {

            std::string Title;
            unsigned int Width, Height;
            bool VSync;
            std::function<void(Event &)> EventCallback;
        };

        WindowData m_data;
    };
}
#endif /* WINDOW_H */