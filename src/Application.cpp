#include "Application.h"

namespace App{
    Application::Application(const AppSpecifications& specs) : m_specs(specs){
        if(!glfwInit()){
            std::cerr << "GLFW INIT ERROR\n";
            return;
        }
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window = glfwCreateWindow(specs.width, specs.height, specs.title.c_str(), nullptr, nullptr);
        if(!m_window){
            std::cerr << "GLFW COULD NOT CREATE WINDOW\n";
            return;
        }

        glfwMakeContextCurrent(m_window);
        glfwSwapInterval(1);

        // Create a unique pointer to GuiRenderer class (unique_ptr is a more memory safe pointer)
        m_gui = std::make_unique<GuiRenderer>(m_window);
    }

    Application::~Application(){
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void Application::Loop(){
        while(!glfwWindowShouldClose(m_window)){
            glfwPollEvents(); // OpenGL poll for events (Mouse movement, Keyboard keys, Window buttons...)

            // Redraw all UI
            ImGui_ImplGlfw_NewFrame();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui::NewFrame();

            m_gui->DrawGUI();

            // Render all ImGui UI
            ImGui::Render();

            // Get OpenGL window size and set Viewport to the same size
            glfwGetFramebufferSize(m_window, &m_framebufferW, &m_framebufferH);
            glViewport(0, 0, m_framebufferW, m_framebufferH);

            // OpenGL set color to clear current back buffer width
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // from 0.0f to 1.0f
            glClear(GL_COLOR_BUFFER_BIT); // OpenGL fill current back buffer with set clear color

            // Finally draw ImGui render data to the screen
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // OpenGL swap back and front buffer to show the newly drawn ImGui data
            glfwSwapBuffers(m_window);
        }
    }
}
