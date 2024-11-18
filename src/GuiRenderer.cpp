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

        if (ImGui::CollapsingHeader("Saved Accounts")) {
            for (int i = 0; i < 10; ++i) {
                ImGui::SetCursorPosX(20);
                std::string label("Youtube.com " + std::to_string(i));
                if (ImGui::CollapsingHeader(label.c_str())) {
                    ImGui::SetCursorPosX(40);
                    ImGui::Text("Username:");
                    ImGui::SameLine();
                    ImGui::TextColored({50,0,255,255},"FGaming");
                    ImGui::SameLine();
                    ImGui::PushID(1);
                    if(ImGui::Button("Copy")) {
                        ImGui::SetClipboardText("Sigma_male");
                    }
                    ImGui::PopID();

                    ImGui::SetCursorPosX(40);
                    ImGui::Text("Password:");
                    ImGui::SameLine();
                    if(ImGui::Button("Reveal password")) {
                        ImGui::OpenPopup("Password");
                    }
                    ImGui::PushID(2);
                    ImGui::SameLine();
                    if(ImGui::Button("Copy")) {
                        ImGui::SetClipboardText("Ilovemen123");
                    }
                    ImGui::PopID();
                }
            }
            ImGui::Text("");
        }

        if (ImGui::BeginPopup("Password"))
        {
            ImGui::Text("Insert password here");
            if (ImGui::Button("Close"))
            {
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if(ImGui::Button("Copy")) {
                ImGui::SetClipboardText("Ilovemen123");
            }
            ImGui::EndPopup();
        }

        if (ImGui::CollapsingHeader("Generate account")) {
            ImGui::Text("Origin: ");
            ImGui::SameLine();
            ImGui::SetCursorPosX(140);
            ImGui::PushItemWidth(255);
            ImGui::InputTextWithHint("##Origin","Example: Youtube.com", m_origin, IM_ARRAYSIZE(m_origin));

            ImGui::Text("Username: ");
            ImGui::SameLine();
            ImGui::SetCursorPosX(140);
            ImGui::InputTextWithHint("##Username", "Example: Susan_Wojicjcjiji",m_username, IM_ARRAYSIZE(m_username));

            ImGui::Text("Password length: ");
            ImGui::SameLine();
            ImGui::SetCursorPosX(140);
            ImGui::SliderInt("Length", &m_passLength, 1, 100);
            ImGui::PopItemWidth();

            static constexpr float buttonWidth = 200;
            ImGui::SetCursorPosX(ImGui::GetWindowWidth()/2-buttonWidth/2);
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(.5f, 0, 0, 1.0f));
            if (ImGui::Button("Generate!", { buttonWidth,20 })) {
                std::cout << "\nGenerating account..." << "\n";
                std::cout << "With password length: " << m_passLength << "\n";
                std::cout << "With username: " << m_username << "\n";
                std::cout << "With origin: " << m_origin;
                m_account a;
                a.origin = m_origin;
                a.username = m_username;
                a.password = "123";

                //m_accounts[sizeof(m_accounts)] = a;
            }
            ImGui::PopStyleColor(1);
        }

        ImGui::End();


    }
}