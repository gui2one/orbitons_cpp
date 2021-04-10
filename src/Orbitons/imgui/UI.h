#ifndef UI_H
#define UI_H

#include "pch.h"
#include "core.h"
#include "imgui.h"
#include "../imgui_impl_glfw.h"
#include "../imgui_impl_opengl3.h"

#include "ImGuizmo.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Events/Event.h"
#include "Events/KeyboardEvent.h"
#include "Core/PlatformUtils.h"
#include "Renderer/FrameBuffer.h"
#include "Renderer/GraphicContext.h"

#include "Scene/Scene.h"
#include "Scene/ResourceLibrary.h"

namespace Orbitons
{

    class UI
    {

    public:
        GraphicContext *m_Context;

        bool isMouseOverViewport = false;
        std::string projectFilePath = std::string("");

    public:
        UI();
        ~UI();

        void init(GLFWwindow *window);

        bool onKeyPressEvent(KeyPressEvent &e);
        void onEvent(Event &e);

        void render(const Ref<FrameBuffer> &frameBuffer);
        void setEventCallback(std::function<void(Event &)> callbackFn) { m_EventCallback = callbackFn; }
        void close();

        ImVec2 getViewportSize();
        bool getViewportSizeChanged();

        void setContext(GraphicContext &ctx) { m_Context = &ctx; }
        void setScene(Scene &scene) { m_scene = &scene; }

        bool saveProject();
        bool saveProjectAs(std::string file_path);
        // panels
        void sceneHierarchyPanel();
        void resourceLibraryPanel();
        void EntityComponentsPanel();

        //components widgets
        void drawTagComponent();
        void drawTransformComponent();
        void drawMeshComponent();
        void drawCameraComponent();
        void drawMaterialComponent();

        //widgets
        void drawVec3Widget(glm::vec3 &vec, const char *label, float default_value = 0.0f);
        void drawColorWidget(glm::vec3 &clr, const char *label, glm::vec3 default_value = glm::vec3(1.f));
        void drawResourceItem(Ref<ResourceItem> &item);

        void initConfirmModal(const char *message, std::function<void()> func);
        void openConfirmModal();
        template <typename T>
        void drawResourceItemTarget(Ref<T> &target, const char *msg = "Set Item Target :")
        {
            ImGui::PushID(&target);

            ImGui::Text("%s", T::GetTypeName());

            if (ImGui::Button("set"))
            {
                target = std::dynamic_pointer_cast<T>(SelectionContext::getInstance().m_selectedResource);
            }

            ImGui::SameLine();

            if (target)
            {
                ImGui::Text(" %s", target->getUUID().c_str());

                if (ImGui::IsItemClicked())
                {
                    SelectionContext::getInstance().m_selectedResource = target;
                }
                if (ImGui::IsItemHovered())
                {
                    ImGui::BeginTooltip();
                    ImGui::Text("Click to highlight in Resource Library");
                    ImGui::EndTooltip();
                }
            }
            else
            {
                ImGui::Text("None");
            }

            ImGui::PopID();
        }

        template <typename T>
        void drawRemoveComponentButton(T &component)
        {
            auto &selected_entity = SelectionContext::getInstance().getSelectedEntity();
            initConfirmModal("Remove Component ?", [&selected_entity]() {
                selected_entity.removeComponent<T>();
            });
            if (ImGui::Button("Remove Component", ImVec2(ImGui::GetContentRegionAvailWidth(), ImGui::GetFontSize() + 4.f)))
            {
                ImGui::OpenPopup("Confirm ?");
            }
        }

    private:
        GLFWwindow *m_window;
        Scene *m_scene;
        ImVec2 m_viewportSize;
        ImVec2 oldSize;
        bool m_viewportSizeChanged = false;

        bool showDemoWindow = false;
        bool b_showViewport = true;

        std::function<void(Event &)> m_EventCallback;

        ImGuizmo::OPERATION m_currentGizmo;
    };
} // namespace Orbitons
#endif /* UI_H */