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
        // panels
        void sceneHierarchyPanel();
        void resourceLibraryPanel();
        void EntityComponentsPanel();

        //components widgets
        void drawTagComponent();
        void drawTransformComponent();
        void drawMeshComponent();

        //widgets
        void drawVec3Widget(glm::vec3 &vec, const char *label, float default_value = 0.0f);
        void drawResourceItem(Ref<ResourceItem> &item);

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