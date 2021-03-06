#include "UI.h"

UI::UI(){
    
}

UI::~UI(){

}

void UI::init(GLFWwindow * window){

    m_window = window;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    const char* glsl_version = "#version 130";
    ImGui_ImplOpenGL3_Init(glsl_version);
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
}

void UI::render(){

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGui::Begin("Properties");  

    ImGui::End();

    // ImGui::ShowDemoWindow(&show_demo_window);

    // Rendering
    ImGui::Render();
    int display_w, display_h;

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}