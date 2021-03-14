#ifndef UI_H
#define UI_H


#include "imgui.h"
#include "../imgui_impl_glfw.h"
#include "../imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Events/Event.h"
#include "Core/PlatformUtils.h"
#include "Renderer/FrameBuffer.h"
#include "Renderer/GraphicContext.h"

#include "core.h"

namespace Orbitons
{
    
    class UI{

    public : 
        GraphicContext* m_Context;
    public:
        UI();
        ~UI();

        void init(GLFWwindow * window);

        void onEvent(Event& e);

        void render(const Orbitons::Ref<Orbitons::FrameBuffer>& frameBuffer);
        void close();

        ImVec2 getViewportSize();
        bool getViewportSizeChanged();

        void setContext(GraphicContext& ctx) { m_Context = &ctx; }
    private:

        GLFWwindow * m_window;
        ImVec2 m_viewportSize;
        ImVec2 oldSize;
        bool m_viewportSizeChanged = false;
        
        bool showDemoWindow = true;
        bool b_showViewport = true;




    };
} // namespace Orbitons
#endif /* UI_H */