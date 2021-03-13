#ifndef UI_H
#define UI_H

#include "glad/glad.h"

#include "imgui.h"
#include "../imgui_impl_glfw.h"
#include "../imgui_impl_opengl3.h"

#include "GLFW/glfw3.h"

#include "core/PlatformUtils.h"
#include "Renderer/FrameBuffer.h"

#include "core.h"
class UI{
public:
    UI();
    ~UI();

    void init(GLFWwindow * window);


    void render(const Orbitons::Ref<Orbitons::FrameBuffer>& frameBuffer);
    ImVec2 getViewportSize();
    bool getViewportSizeChanged() { 
        bool temp = m_viewportSizeChanged;
        if(temp){
            m_viewportSizeChanged = false;
            return true;
        }
        return false; 
    };
private:

    GLFWwindow * m_window;
    ImVec2 m_viewportSize;
    ImVec2 oldSize;
    bool m_viewportSizeChanged = false;
    
    bool showDemoWindow = true;
    bool b_showViewport = true;




};
#endif /* UI_H */