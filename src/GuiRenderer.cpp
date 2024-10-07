#include "GuiRenderer.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

namespace App{
    GuiRenderer::GuiRenderer(GLFWwindow* window){
        // Initialize ImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        m_io = &ImGui::GetIO(); (void)m_io;
        m_io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        // m_io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        ImGui::StyleColorsDark(); // Dark mode (Classic | Light | Dark)

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(m_glslVersion.c_str());
    }

    GuiRenderer::~GuiRenderer(){
        delete m_io;
    }

    void GuiRenderer::DrawGUI(){
        ImGui::ShowDemoWindow();
    }
}