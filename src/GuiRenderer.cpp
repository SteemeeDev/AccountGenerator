#include "GuiRenderer.h"

#include <imgui_internal.h>
#include <iostream>
#include <ostream>

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

namespace App{
    GuiRenderer::GuiRenderer(GLFWwindow* window){
        m_window = window;
        // Initialize ImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        m_io = &ImGui::GetIO(); (void)m_io;
        m_io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        ImGui::StyleColorsDark(); // Dark mode (Classic | Light | Dark)

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(m_glslVersion.c_str());

        m_windowFlags |= ImGuiWindowFlags_NoResize;
        m_windowFlags |= ImGuiWindowFlags_NoMove;
        m_windowFlags |= ImGuiWindowFlags_NoCollapse;
        m_windowFlags |= ImGuiWindowFlags_MenuBar;
        m_windowFlags |= ImGuiWindowFlags_NoTitleBar;

        glfwGetWindowSize(m_window, &m_width, &m_height);
    }

    GuiRenderer::~GuiRenderer(){
        m_io = nullptr;
    }

    void GuiRenderer::DrawGUI(){

        ImGui::Begin("Password Generator", nullptr, m_windowFlags);

        ImGui::SetWindowPos({ 0,0 });
        ImGui::SetWindowSize({static_cast<float>(m_width), static_cast<float>(m_height)});

        if(ImGui::BeginMenuBar()){
            if(ImGui::BeginMenu("File")){
                if(ImGui::MenuItem("Ligma")){
                    std::clog << "LIGAMA\n";
                }
                if(ImGui::MenuItem("BALLS")){
                    std::clog << "BALALAS\n";
                }
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        if (ImGui::CollapsingHeader("Saved passwords")) {
            ImGui::Text("Saved passwords:");
        }

        if (ImGui::CollapsingHeader("Generate Passwords")) {
            ImGui::Text("Password length: ");
            ImGui::SameLine();
            ImGui::SliderInt("Length", &m_passLength, 1, 100);
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(.5f, 0, 0, 1.0f));
            if (ImGui::Button("Generate!")) {
                std::cout << "Generating Password with length " << m_passLength << std::endl;

            }
            ImGui::PopStyleColor(1);
        }

        if(ImGui::CollapsingHeader("Generate Username")) {
            ImGui::Text("Generate Username");
        }

        ImGui::End();


    }
}