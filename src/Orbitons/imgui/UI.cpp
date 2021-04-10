#include <typeinfo>

#include "UI.h"
#include "Events/Event.h"
#include "Events/KeyboardEvent.h"
#include "Scene/Components.h"
#include "entt/entt.hpp"
#include "Scene/Entity.h"
#include "Scene/ResourceLibrary.h"
#include "Scene/SelectionContext.h"

#include "ImGuizmo.h"
#include "../vendor/imgui/imgui_internal.h"

#include "Core/Serializer.h"
// #include "Core/IDGenerator.h"

namespace Orbitons
{

    UI::UI()
        : m_Context(nullptr), m_viewportSize(ImVec2(256, 256))
    {
        oldSize = m_viewportSize;
    }

    UI::~UI()
    {
    }

    void UI::init(GLFWwindow *window)
    {

        m_window = window;

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.Fonts->AddFontFromFileTTF(ORBITONS_RES_DIR "/fonts/JetBrainsMono-Regular.ttf", 16);
        io.ConfigDockingWithShift = false;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImVec4 *colors = ImGui::GetStyle().Colors;
        // small scope to tidy a little
        {

            ImVec4 *colors = ImGui::GetStyle().Colors;
            colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
            colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
            colors[ImGuiCol_WindowBg] = ImVec4(0.12f, 0.12f, 0.12f, 0.94f);
            colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
            colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
            colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
            colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
            colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
            colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
            colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
            colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
            colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
            colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
            colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
            colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
            colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
            colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
            colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
            colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
            colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
            colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
            colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
            colors[ImGuiCol_Header] = ImVec4(1.00f, 0.73f, 0.34f, 0.52f);
            colors[ImGuiCol_HeaderHovered] = ImVec4(0.95f, 0.65f, 0.20f, 0.82f);
            colors[ImGuiCol_HeaderActive] = ImVec4(0.96f, 0.53f, 0.21f, 0.94f);
            colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
            colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
            colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
            colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
            colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
            colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
            colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.35f, 0.58f, 0.86f);
            colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
            colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.41f, 0.68f, 1.00f);
            colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
            colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
            colors[ImGuiCol_DockingPreview] = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);
            colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
            colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
            colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
            colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
            colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
            colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
            colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
            colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
            colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
            colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
            colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
            colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
            colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
            colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
            colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
        }

        ImGui::GetStyle().WindowMenuButtonPosition = ImGuiDir_Left;
        ImGui_ImplGlfw_InitForOpenGL(m_window, true);
        const char *glsl_version = "#version 130";
        ImGui_ImplOpenGL3_Init(glsl_version);

        m_currentGizmo = ImGuizmo::OPERATION::TRANSLATE;
    }

    ImVec2 UI::getViewportSize()
    {

        return m_viewportSize;
    }

    bool UI::getViewportSizeChanged()
    {
        bool temp = m_viewportSizeChanged;
        if (temp)
        {
            m_viewportSizeChanged = false;
            return true;
        }
        return false;
    }

    bool UI::saveProject()
    {
        if (projectFilePath == "")
        {
            std::optional<std::string> path = PlatformUtils::saveFileDialog("Orbitons\0 *.orbitons\0");

            if (path)
            {
                projectFilePath = path->data();
                glfwSetWindowTitle(m_window, projectFilePath.c_str());
                return saveProjectAs(path->data());
            }
        }
        else
        {
            glfwSetWindowTitle(m_window, projectFilePath.c_str());
            return saveProjectAs(projectFilePath);
        }
        // printf("Saving project\n");
        return true;
    }

    bool UI::saveProjectAs(std::string file_path)
    {
        projectFilePath = file_path;
        glfwSetWindowTitle(m_window, projectFilePath.c_str());

        Serializer serializer;

        YAML::Emitter emitter;

        emitter << serializer.serializeScene(m_scene);
        emitter << serializer.serializeResources(ResourceLibrary::getInstance());

        std::ofstream out(file_path.c_str());
        out << emitter.c_str();
        return true;
    }
    bool UI::onKeyPressEvent(KeyPressEvent &e)
    {
        const char *key_name = glfwGetKeyName(e.m_Keycode, e.m_Scancode);

        ImGuiIO &io = ImGui::GetIO();

        if (key_name)
        {

            switch (key_name[0])
            {
            case NULL:
                return true;
            case 's':
                if (io.KeyCtrl)
                    saveProject();
                return true;
            case 'z':
                // printf("translate\n", key_name);
                m_currentGizmo = ImGuizmo::OPERATION::TRANSLATE;
                return true;
            case 'e':
                // printf("scale\n", key_name);
                m_currentGizmo = ImGuizmo::OPERATION::SCALE;
                return true;
            case 'r':
                // printf("rotate\n", key_name);
                m_currentGizmo = ImGuizmo::OPERATION::ROTATE;
                return true;
            default:
                return true;
            }
        }

        if (e.m_Keycode == GLFW_KEY_SPACE)
        {
            printf("haaaaa!!!!!!\n");
            return false;
        }

        return false;
    }

    void UI::onEvent(Event &e)
    {

        // printf("------------ %s\n", e.GetName());
        Dispatcher dispatcher(e);
        dispatcher.dispatch<KeyPressEvent>(BIND_EVENT_FUNCTION(UI::onKeyPressEvent));
    }

    void UI::render(const Ref<FrameBuffer> &frameBuffer)
    {

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGuizmo::BeginFrame();
        bool active = true;

        if (active)
        {
            // Declare Central dockspace

            ImGui::DockSpaceOverViewport(NULL, ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode /*|ImGuiDockNodeFlags_NoResize*/);
        }

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        if (ImGui::BeginMainMenuBar())
        {

            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open ..."))
                {

                    std::optional<std::string> path = PlatformUtils::openFileialog("../../resources/shaders/phong_shader.frag", "Orbitons\0 *.orbitons\0");

                    if (path)
                    {
                        Serializer serializer;
                        serializer.deserialize(path->data(), m_scene, ResourceLibrary::getInstance());
                        projectFilePath = path->data();
                        glfwSetWindowTitle(m_window, projectFilePath.c_str());
                    }
                }
                if (ImGui::MenuItem("Save as ..."))
                {
                    std::optional<std::string> path = PlatformUtils::saveFileDialog("Orbitons\0 *.orbitons\0");

                    if (path)
                    {
                        saveProjectAs(path->data());
                    }
                }

                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("About"))
            {
                if (ImGui::MenuItem(" ..."))
                {
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Misc"))
            {
                if (ImGui::MenuItem("Show Demo Window", "", &showDemoWindow))
                {
                }

                if (ImGui::MenuItem("Show Viewport", "", &b_showViewport))
                {
                }

                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        ImGui::Begin("Infos");

        size_t memory_usage = PlatformUtils::getMemoryUsage();
        ImGui::Text("Memory used : %d Mb", memory_usage / 1024 / 1024);
        ImGui::Separator();
        ImGui::Text("Graphic Context : %s", m_Context->getVersion());
        ImGui::Text("Shading Language : %s", m_Context->getShadingLanguageVersion());

        ImGui::End();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

        // .WindowMenuButtonPosition = ImGuiDir_None;
        ImGuiWindowFlags flags = 0;

        // flags |= ImGuiWindowFlags_Window;

        if (ImGui::Begin("Viewport", NULL, flags))
        {
            // Get the size of the child (i.e. the whole draw size of the windows).
            m_viewportSize = ImGui::GetContentRegionAvail();
            if (m_viewportSize.x != oldSize.x || m_viewportSize.y != oldSize.y)
            {

                m_viewportSizeChanged = true;
                oldSize = m_viewportSize;
            }
            // Because I use the texture from OpenGL, I need to invert the V from the UV.
            // "double cast" (ImTextureID)(intptr_t) needed to prevent a warning about convertion size. Maybe not prudent
            ImGui::Image((ImTextureID)(intptr_t)frameBuffer->getID(), m_viewportSize, ImVec2(0, 1), ImVec2(1, 0));
            Entity selectedEntity = SelectionContext::getInstance().getSelectedEntity();

            if (selectedEntity)
            {
                glm::mat4 matrix(1.0f);
                if (selectedEntity.hasComponent<TransformComponent>())
                {

                    auto &trans = selectedEntity.getComponent<TransformComponent>();
                    matrix = trans.getTransforms();
                }

                float windowWidth = (float)m_viewportSize.x;
                float windowHeight = (float)m_viewportSize.y;

                ImGuizmo::SetOrthographic(false);
                ImGuizmo::SetDrawlist();
                ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

                glm::vec3 up_vector(0.f, 1.0f, 0.f);
                glm::mat4 camProjection = m_scene->m_activeCamera->projection;
                glm::mat4 camView = glm::mat4(1.0f) * glm::lookAt(
                                                          m_scene->m_activeCamera->position,
                                                          m_scene->m_activeCamera->target_position,
                                                          glm::normalize(up_vector));

                ImGuizmo::Manipulate(glm::value_ptr(camView), glm::value_ptr(camProjection), m_currentGizmo, ImGuizmo::LOCAL, glm::value_ptr(matrix));

                if (ImGuizmo::IsUsing())
                {
                    glm::vec3 scale, translation, skew;
                    glm::quat orient;
                    glm::vec4 perspective;
                    glm::decompose(matrix, scale, orient, translation, skew, perspective);
                    if (selectedEntity.hasComponent<TransformComponent>())
                    {

                        auto &trans = selectedEntity.getComponent<TransformComponent>();
                        trans.position = translation;
                        trans.rotation = glm::degrees(glm::eulerAngles(orient));
                        trans.scale = scale;
                    }
                }
            }

            isMouseOverViewport = ImGui::IsItemHovered();
            // printf("over viewport %s\n", isMouseOverViewport ? "true" : "false");

            ImGui::End();
        }

        ImGui::PopStyleVar();

        sceneHierarchyPanel();
        resourceLibraryPanel();
        EntityComponentsPanel();

        if (showDemoWindow)
        {

            ImGui::ShowDemoWindow(&showDemoWindow);
        }

        // Rendering
        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGui::EndFrame();

        ImGuiIO &io = ImGui::GetIO();

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();

            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();

            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void UI::close()
    {

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void UI::sceneHierarchyPanel()
    {
        ImGui::Begin("Scene");

        auto view = m_scene->m_registry.view<TagComponent>();

        int inc = 0;
        static uint64_t selection_id = 0;

        SelectionContext &Selection = SelectionContext::getInstance();

        if (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered())
        {

            Selection.setSelectedEntity(Entity(entt::null, m_scene));
        }
        if (ImGui::Button("Add Entity"))
        {
            m_scene->createEntity("new entity");
        }
        for (auto entity : view)
        {
            Entity ent{entity, m_scene};
            // printf("Entity %d --tag name : %s\n", inc, view.get<TagComponent>(entity).tagName.c_str());

            ImGuiTreeNodeFlags flags = 0;
            flags |= ((Selection.m_selectedEntity) == entity ? ImGuiTreeNodeFlags_Selected : 0);
            flags |= ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_OpenOnArrow;
            bool opened = ImGui::TreeNodeEx((void *)entity, flags, view.get<TagComponent>(entity).tagName.c_str());
            if (ImGui::IsItemClicked())
            {

                // SelectionContext::getInstance().setSelectedEntity(entity);

                Selection.setSelectedEntity(ent);
            }
            ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - 15);
            ImGui::PushID(inc);

            initConfirmModal("Remove Entity ?", [&]() {
                m_scene->destroyEntity(entity);
                if (Selection.m_selectedEntity == entity)
                {
                    Selection.m_selectedEntity = {};
                }
            });
            if (ImGui::Button("x"))
            {
                openConfirmModal();
            }
            ImGui::PopID();
            if (opened)
            {
                ImGui::Text("UUID : %s", ent.getComponent<UUIDComponent>().uuid.c_str());
                ImGui::TreePop();
            }
            inc++;
        }

        ImGui::End();
    }

    void UI::resourceLibraryPanel()
    {

        ImGuiWindowFlags flags = 0;
        flags |= ImGuiWindowFlags_MenuBar;

        ImGui::Begin("Resource Library", NULL, flags);

        if (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered())
        {

            SelectionContext::getInstance().m_selectedResource = nullptr;
        }

        // menu bar
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Add"))
            {
                if (ImGui::Selectable("Mesh"))
                {
                    std::optional<std::string> file_path = PlatformUtils::openFileialog("");
                    if (file_path)
                    {

                        Ref<MeshItem> item = MakeRef<MeshItem>(file_path.value());
                        ResourceLibrary::getInstance().addItem(item);
                    }
                }

                if (ImGui::Selectable("Texture"))
                {
                    std::optional<std::string> file_path = PlatformUtils::openFileialog("", "All(*.png;*.jpg)\0 *.png;*.jpg\0");
                    if (file_path)
                    {
                        Ref<TextureItem> item = MakeRef<TextureItem>(file_path.value());
                        ResourceLibrary::getInstance().addItem(item);
                    }
                }
                ImGui::Separator();

                if (ImGui::BeginMenu("Material"))
                {
                    if (ImGui::Selectable("Unlit"))
                    {
                        printf("adding Unlit Material\n");
                        Ref<UnlitMaterialItem> item = MakeRef<UnlitMaterialItem>();
                        ResourceLibrary::getInstance().addItem(item);
                    }

                    if (ImGui::Selectable("Phong"))
                    {
                        Ref<PhongMaterialItem> item = MakeRef<PhongMaterialItem>();
                        ResourceLibrary::getInstance().addItem(item);
                        printf("adding Phong Material\n");
                    }

                    ImGui::EndMenu();
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::Selectable("Delete All Resources"))
                {
                    ResourceLibrary::getInstance().items.clear();
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        static bool selected = false;
        int inc_id = 0;
        for (auto item : ResourceLibrary::getInstance().items)
        {
            drawResourceItem(item);
        }
        ImGui::End();
    }

    void UI::drawResourceItem(Ref<ResourceItem> &item)
    {
        ImGui::PushID(item.get());

        ImVec4 clr(1.0f, 0.2f, 0.2f, 1.0f);

        switch (item->GetItemType())
        {

        case ResourceItemType::MeshItem:
            // printf("drawing meshItem\n");
            clr = ImVec4(0.2f, 0.8f, 0.2f, 1.0f);
            break;
        case ResourceItemType::TextureItem:
            // printf("drawing meshItem\n");
            clr = ImVec4(1.0f, 0.2f, 0.3f, 1.0f);
            break;
        case ResourceItemType::MaterialItem:
            // printf("drawing meshItem\n");
            clr = ImVec4(0.2f, 0.2f, 0.9f, 1.0f);
            break;
        }

        ImGui::PushStyleColor(ImGuiCol_Text, clr);

        if (ImGui::Selectable(item->GetName(), SelectionContext::getInstance().m_selectedResource == item))
        {
            SelectionContext::getInstance().m_selectedResource = item;
        }

        ImGui::PopStyleColor();

        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();

            ImGui::Text(item->GetName());
            if (item->GetItemType() == ResourceItemType::TextureItem)
            {

                Ref<TextureItem> texture_item = std::dynamic_pointer_cast<TextureItem>(item);
                ImGui::SameLine();
                ImGui::Text(" : %d / %d", texture_item->texture->getWidth(), texture_item->texture->getHeight());
                float max_dim = 512.f;
                ImVec2 texture_size = ImVec2((float)texture_item->texture->getWidth(), (float)texture_item->texture->getHeight());
                ImVec2 image_size = texture_size;

                if (texture_size.x > max_dim)
                {
                    float width_ratio = texture_size.x / texture_size.y;
                    image_size.x = max_dim;
                    image_size.y = max_dim / width_ratio;
                }

                ImGui::Image((ImTextureID)(intptr_t)texture_item->texture->getID(), image_size, ImVec2(0, 1), ImVec2(1, 0));
            }

            ImGui::EndTooltip();
        }
        ImGui::SameLine();
        ImGui::Text(" | path: %s", item->path.c_str());
        ImGui::Separator();

        ImGui::PopID();
    }

    void UI::initConfirmModal(const char *message, std::function<void()> func)
    {
        auto &selected_entity = SelectionContext::getInstance().getSelectedEntity();
        // Always center this window when appearing
        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        if (ImGui::BeginPopupModal("Confirm ?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("%s", message);
            if (ImGui::Button("Yes"))
            {
                func();
                // selected_entity.removeComponent<T>();
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            ImGui::SetItemDefaultFocus();
            if (ImGui::Button("No"))
            {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
    }

    void UI::openConfirmModal()
    {
        ImGui::OpenPopup("Confirm ?");
    }

    void UI::drawVec3Widget(glm::vec3 &vec, const char *label, float default_value)
    {
        ImGui::PushID(label);
        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, 90.f);

        ImGui::Text("%s", label);

        ImGui::NextColumn();
        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 0.f));
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0.8f, 0.1f, 0.1f, 1.f)));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(0.9f, 0.1f, 0.1f, 1.f)));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(1.0f, 0.1f, 0.1f, 1.f)));

        if (ImGui::Button("X", ImVec2(30, 20)))
        {
            vec.x = default_value;
        }

        ImGui::PopStyleColor(3);
        ImGui::SameLine();
        ImGui::DragFloat("##x", &vec.x, 0.05f);
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0.1f, 0.5f, 0.1f, 1.f)));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(0.1f, 0.6f, 0.1f, 1.f)));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(0.1f, 0.7f, 0.1f, 1.f)));
        if (ImGui::Button("Y", ImVec2(30, 20)))
        {
            vec.y = default_value;
        }
        ImGui::PopStyleColor(3);
        ImGui::SameLine();
        ImGui::DragFloat("##y", &vec.y, 0.05f);
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0.1f, 0.1f, 0.8f, 1.f)));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(0.1f, 0.1f, 0.9f, 1.f)));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(0.1f, 0.1f, 1.0f, 1.f)));
        if (ImGui::Button("Z", ImVec2(30, 20)))
        {
            vec.z = default_value;
        }
        ImGui::PopStyleColor(3);
        ImGui::SameLine();
        ImGui::DragFloat("##z", &vec.z, 0.05f);

        ImGui::PopItemWidth();
        ImGui::Columns(1);
        ImGui::PopStyleVar();
        ImGui::PopID();
    }

    void UI::drawColorWidget(glm::vec3 &clr, const char *label, glm::vec3 default_value)
    {
        ImGuiColorEditFlags flags = 0;
        flags |= ImGuiColorEditFlags_Float;
        flags |= ImGuiColorEditFlags_NoInputs;
        if (ImGui::ColorEdit3(label, glm::value_ptr(clr), flags))
        {
        }
    }

    /*
    -------------------------
        Components
    -------------------------
    */

    void UI::EntityComponentsPanel()
    {
        ImGui::Begin("Components");
        if (SelectionContext::getInstance().getSelectedEntity())
        {

            if (ImGui::BeginCombo("Add Component", ""))
            {
                Entity entity = SelectionContext::getInstance().getSelectedEntity();
                if (ImGui::Selectable("Transform"))
                {
                    if (!entity.hasComponent<TransformComponent>())
                    {
                        m_scene->m_registry.emplace<TransformComponent>(entity, glm::vec3(0.f));
                    }
                }
                if (ImGui::Selectable("Mesh"))
                {
                    if (!entity.hasComponent<MeshComponent>())
                    {
                        // crashes
                        // need more stuff

                        Ref<MeshObject> mesh_oject = MakeRef<MeshObject>(); //
                        mesh_oject->setMesh(MeshUtils::makeGrid(1.f, 1.f, 2, 2));

                        MeshUtils::rotateX(mesh_oject->m_mesh, -PI / 2.0f);
                        // MeshUtils::computeNormals(mesh_oject->m_mesh);
                        mesh_oject->buildBuffers();
                        m_scene->m_registry.emplace<MeshComponent>(entity);
                    }
                }
                if (ImGui::Selectable("Camera"))
                {

                    if (!entity.hasComponent<CameraComponent>())
                    {
                        m_scene->m_registry.emplace<CameraComponent>(entity);
                    }
                }
                if (ImGui::Selectable("Material"))
                {

                    if (!entity.hasComponent<MaterialComponent>())
                    {
                        m_scene->m_registry.emplace<MaterialComponent>(entity);
                        entity.getComponent<MaterialComponent>().material_item = m_scene->m_defaultMaterialItem;
                        printf("------------- adding default material\n");
                    }
                }
                ImGui::EndCombo();
            }
            drawTagComponent();
            drawTransformComponent();
            drawMeshComponent();
            drawCameraComponent();
            drawMaterialComponent();
        }

        ImGui::End();
    }

    void UI::drawTagComponent()
    {

        Entity ent = SelectionContext::getInstance().m_selectedEntity;
        if (ent.hasComponent<TagComponent>())
        {
            ImGuiTreeNodeFlags flags = 0;
            flags |= ImGuiTreeNodeFlags_DefaultOpen;
            if (ImGui::CollapsingHeader("Tag Component", flags))
            {

                std::string tagName = ent.getComponent<TagComponent>().tagName;
                char *buff = (char *)(tagName.c_str());
                if (ImGui::InputText("Tag Name", buff, 256))
                {
                    tagName = std::string(buff);
                    m_scene->m_registry.replace<TagComponent>(ent, tagName);
                }
            }
        }
    }

    void UI::drawTransformComponent()
    {
        Entity ent = SelectionContext::getInstance().m_selectedEntity;
        if (ent.hasComponent<TransformComponent>())
        {
            auto &transforms = ent.getComponent<TransformComponent>();
            ImGuiTreeNodeFlags flags = 0;
            flags |= ImGuiTreeNodeFlags_DefaultOpen;
            if (ImGui::CollapsingHeader("Transform Component", flags))
            {
                drawVec3Widget(transforms.position, "position");
                drawVec3Widget(transforms.rotation, "rotation");
                drawVec3Widget(transforms.scale, "scale", 1.0f);

                ImGui::PushID("remove_transform_component");
                if (ImGui::Button("remove"))
                {
                    ent.removeComponent<TransformComponent>();
                }

                ImGui::PopID();
            }
        }
    }

    void UI::drawCameraComponent()
    {
        Entity ent = SelectionContext::getInstance().m_selectedEntity;
        if (ent.hasComponent<CameraComponent>())
        {

            auto &camera = ent.getComponent<CameraComponent>();
            ImGuiTreeNodeFlags flags = 0;
            flags |= ImGuiTreeNodeFlags_DefaultOpen;
            if (ImGui::CollapsingHeader("Camera Component", flags))
            {
                ImGui::Checkbox("Active", &(camera.active));
                ImGui::DragFloat("angle", &(camera.angle));
                ImGui::DragFloat("near", &(camera.near));
                ImGui::DragFloat("far", &(camera.far));

                ImGui::PushID("remove_camera_component");
                if (ImGui::Button("remove"))
                {
                    ent.removeComponent<CameraComponent>();
                }

                ImGui::PopID();
            }
        }
    }

    void UI::drawMeshComponent()
    {
        Entity ent = SelectionContext::getInstance().m_selectedEntity;
        if (ent.hasComponent<MeshComponent>())
        {

            auto &meshComp = ent.getComponent<MeshComponent>();
            ImGui::PushID(&meshComp);
            ImGuiTreeNodeFlags flags = 0;
            flags |= ImGuiTreeNodeFlags_DefaultOpen;
            if (ImGui::CollapsingHeader("Mesh Component", flags))
            {
                drawResourceItemTarget<MeshItem>(meshComp.mesh_item, "set mesh target :");
                drawRemoveComponentButton<MeshComponent>(meshComp);
            }
            ImGui::PopID();
        }
    }

    void UI::drawMaterialComponent()
    {
        Entity ent = SelectionContext::getInstance().m_selectedEntity;
        if (ent.hasComponent<MaterialComponent>())
        {

            auto &material = ent.getComponent<MaterialComponent>();
            ImGui::PushID(&material);
            ImGuiTreeNodeFlags flags = 0;
            flags |= ImGuiTreeNodeFlags_DefaultOpen;
            if (ImGui::CollapsingHeader("Material Component", flags))
            {
                drawResourceItemTarget<MaterialItem>(material.material_item, "set Material Item :");

                if (material.material_item)
                {

                    if (material.material_item->material_type == MaterialItemType::Phong)
                    {

                        ImGui::Text("Phong");
                        static glm::vec3 clr(1.f, 0.f, 0.f);
                        Ref<PhongMaterial> phong = std::dynamic_pointer_cast<PhongMaterial>(material.material_item->material);
                        if (phong)
                        {

                            drawColorWidget(phong->diffuseColor, "DiffuseColor");
                        }
                        else
                        {
                            ImGui::Text("Problem");
                        }
                    }
                    else if (material.material_item->material_type == MaterialItemType::Unlit)
                    {
                        ImGui::Text("Unlit");
                    }
                    else
                    {
                        ImGui::Text("Bad !!!!!");
                    }
                }
                ImGui::Separator();

                drawRemoveComponentButton<MaterialComponent>(material);
            }
            ImGui::PopID();
        }
    }

} // namespace Orbitons
