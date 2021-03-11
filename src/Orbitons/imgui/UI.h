#ifndef UI_H
#define UI_H

#include "glad/glad.h"

#include "imgui.h"
#include "../imgui_impl_glfw.h"
#include "../imgui_impl_opengl3.h"

#include "GLFW/glfw3.h"

#include "core/PlatformUtils.h"

class UI{
public:
    UI();
    ~UI();

    void init(GLFWwindow * window);


    void render();
private:

    GLFWwindow * m_window;




};
#endif /* UI_H */