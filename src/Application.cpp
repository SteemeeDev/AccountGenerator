#include "Application.h"

#include <iostream>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include "FileUtil.h"

namespace App{
    Application::Application(AppSpecs specs) : m_specs(std::move(specs)){
        // Attempt to initialize glfw. If not return an error
        if(!glfwInit()){
            std::cerr << "GLFW did not initialize\n";
            return;
        }

        // Set OpenGL version to 3.3 and use the core version for MAX POWER
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, false);

        // Create a GLFWwindow with width, height, and title. No monitor and no share
        m_window = glfwCreateWindow(m_specs.width, m_specs.height, m_specs.title.c_str(), nullptr, nullptr);
        if(!m_window){ // If the window is still a nullptr we could not create a window
            std::cerr << "GLFW could not create OpenGL window!\n";
            return;
        }

        glfwMakeContextCurrent(m_window);
        glfwSwapInterval(1); // vsync

        m_gui = std::make_unique<GuiRenderer>(m_window);
    }


    Application::~Application(){
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void Application::Loop(){
        while(!glfwWindowShouldClose(m_window)){
            glfwPollEvents(); // Look for new events (Mouse move, Keyboard press, Window X button press)

            ImGui_ImplGlfw_NewFrame();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui::NewFrame();

            m_gui->DrawGUI();

            ImGui::Render();

            glfwGetFramebufferSize(m_window, &m_framebufferWidth, &m_framebufferHeight); // Get the size of the frame buffer
            glViewport(0, 0, m_framebufferWidth, m_framebufferHeight); // Set the viewport to the same size as the framebuffer

            // Set a color we can clear the back buffer width (from 0.0f to 1.0f)
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
            // Clear the backbuffer with the set clear color
            glClear(GL_COLOR_BUFFER_BIT);

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // Final swap front and backbuffers
            glfwSwapBuffers(m_window);
        }
    }
}
