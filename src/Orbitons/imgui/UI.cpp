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
    ImGuiIO& io = ImGui::GetIO();


    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; 

    // io.ConfigDockingWithShift = true;
    
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

     bool active = true;
 
    if (active)
    {
        // Declare Central dockspace

        ImGui::DockSpaceOverViewport(NULL, ImGuiDockNodeFlags_None|ImGuiDockNodeFlags_PassthruCentralNode /*|ImGuiDockNodeFlags_NoResize*/);
    }



    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    if(ImGui::BeginMainMenuBar()){

        if(ImGui::BeginMenu("File")){
            if(ImGui::MenuItem("Open ...")){

                std::optional<std::string> path = PlatformUtils::openFileialog("../../resources/shaders/phong_shader.frag");

                if( path )
                    printf("File Path  --> %s\n", path->c_str());
                else    
                    printf("No file \n");
            }            
            if(ImGui::MenuItem("Save as ...")){
                
            }

            ImGui::EndMenu();
        }
        if(ImGui::BeginMenu("About")){
            if(ImGui::MenuItem(" ...")){
                
            }         

            ImGui::EndMenu();  
        }
        ImGui::EndMainMenuBar();
    }


    
    
    ImGui::Begin("Properties");
    ImGui::End();

    ImGui::Begin("Viewport");
    ImGui::End();

    // ImGui::ShowDemoWindow(&show_demo_window);


    // Rendering
    ImGui::Render();
    int display_w, display_h;

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    ImGuiIO& io = ImGui::GetIO();

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }	    

}