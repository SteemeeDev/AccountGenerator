#ifndef GUI_RENDERER_H
#define GUI_RENDERER_H

#include "../vendor/imgui.h"
#include "../vendor/backends/imgui_impl_glfw.h"
#include "../vendor/backends/imgui_impl_opengl3.h"

#include <memory>
#include <string>

namespace gui{
    class GuiRenderer{
    public:
        GuiRenderer(GLFWwindow* window);
        virtual ~GuiRenderer();

        void DrawGUI();

    private:
        const std::string m_glslVersion{"#version 330"};
        ImGuiIO* m_io;
    };
}

#endif