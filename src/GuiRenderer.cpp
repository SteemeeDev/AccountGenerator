#include "GuiRenderer.h"

#include <imgui_internal.h>
#include <iostream>
#include <ostream>
#include <filesystem>
#include <bits/fs_dir.h>

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "FileUtil.h"

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


        m_fileUtil.ReadFile();
    }

    GuiRenderer::~GuiRenderer(){
        m_io = nullptr;
    }

    void GuiRenderer::DrawGUI(){

        ImGui::Begin("Password Generator", nullptr, m_windowFlags);

        ImGui::SetWindowPos({ 0,0 });
        ImGui::SetWindowSize({static_cast<float>(m_width), static_cast<float>(m_height)});

        if (ImGui::CollapsingHeader("Saved Accounts")) {
            if (ImGui::Button("Delete ALL saved accounts")) {
                ImGui::OpenPopup("Confirm");
            }
            std::vector<std::string> accounts = m_fileUtil.GetAccounts();
            for (int i = 0; i < accounts.size(); ++i) {
                ImGui::SetCursorPosX(20);
                std::string label(accounts[i]);
                if (ImGui::CollapsingHeader(label.c_str())) {
                    ImGui::PushID(i);
                    ImGui::SetCursorPosX(40);
                    ImGui::Text("Username:");
                    ImGui::SameLine();
                    ImGui::TextColored({20,0,255,255},m_fileUtil.ShowUname(accounts[i]).c_str());
                    ImGui::SameLine();
                    if(ImGui::Button("Copy##1")) {
                        ImGui::SetClipboardText(m_fileUtil.ShowUname(accounts[i]).c_str());
                    }
                    ImGui::SetCursorPosX(40);
                    ImGui::Text("Password:");
                    ImGui::SameLine();
                    if(ImGui::Button("Reveal password##2")) {
                        ImGui::OpenPopup("Password");
                    }
                    if (ImGui::BeginPopup("Password"))
                    {
                        ImGui::Text(m_fileUtil.ShowPasswd(accounts[i], m_firstFrame).c_str());
                        if (ImGui::Button("Close##4"))
                        {
                            ImGui::CloseCurrentPopup();
                        }
                        ImGui::SameLine();
                        if(ImGui::Button("Copy##5")) {
                            ImGui::SetClipboardText(m_fileUtil.ShowPasswd(accounts[i], m_firstFrame).c_str());
                        }
                        ImGui::EndPopup();
                    }
                    ImGui::SameLine();

                    if(ImGui::Button("Copy##6")) {
                        ImGui::SetClipboardText(m_fileUtil.ShowPasswd(accounts[i], m_firstFrame).c_str());
                    }
                    ImGui::PopID();
                }
            }
            ImGui::Text("");
        }

        if(ImGui::BeginPopup("Confirm")) {
            if (ImGui::Button("confirm")) {
                std::cout << "Saved Accounts deleted" << std::endl;
                std::filesystem::remove("Database");
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel")) {
                ImGui::CloseCurrentPopup();
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
            ImGui::InputTextWithHint("##Username", "Example: Susan_Wojicjcjiji", m_username, IM_ARRAYSIZE(m_username));

            ImGui::Text("Password length: ");
            ImGui::SameLine();
            ImGui::SetCursorPosX(140);
            ImGui::SliderInt("Length", &m_passLength, 1, 100);
            ImGui::PopItemWidth();

            static constexpr float buttonWidth = 200;
            ImGui::SetCursorPosX(ImGui::GetWindowWidth()/2-buttonWidth/2);

            if (m_username[0] != '\0' && m_origin[0] != '\0') {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0.5f, 0, 1.0f));
            }else {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5f, 0, 0, 1.0f));
            }
            if (ImGui::Button("Generate!", { buttonWidth,20 }) && m_username[0] != '\0' && m_origin[0] != '\0') {
                std::cout << "\nGenerating account..." << "\n";
                std::cout << "With password length: " << m_passLength << "\n";
                std::cout << "With username: " << m_username << "\n";
                std::cout << "With origin: " << m_origin;

                m_fileUtil.NewEntry(m_origin, m_username, m_fileUtil.genRandomString(m_passLength));
                m_fileUtil.ReadFile();
            }
            ImGui::PopStyleColor(1);
        }

        ImGui::End();


    }
}