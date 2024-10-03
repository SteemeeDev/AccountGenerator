#include "GuiRenderer.h"

namespace gui{
    GuiRenderer::GuiRenderer(GLFWwindow* window){
        // Initialize DearImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        // Enable Input Output for Keyboard and Gamepads + Enable window docking
        m_io = &ImGui::GetIO(); (void)m_io;
        m_io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        m_io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        m_io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        ImGui::StyleColorsDark(); // Set ImGui Style to dark mode ( Dark | Light | Classic )

        ImGui_ImplGlfw_InitForOpenGL(window, true); // Initialize ImGui with OpenGL & GLFW
        ImGui_ImplOpenGL3_Init(m_glslVersion.c_str()); // Init ImGui with the correct GLSL version
    }

    GuiRenderer::~GuiRenderer(){
        
    }

    void GuiRenderer::DrawGUI(){
        ImGui::ShowDemoWindow();
    }
}