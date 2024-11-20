#ifndef GUIRENDERER_H
#define GUIRENDERER_H

#include "imgui/imgui.h"

#include <string>
#include <GLFW/glfw3.h>

#include "FileUtil.h"

namespace App{

    class GuiRenderer {
    public:
        GuiRenderer(GLFWwindow* window);
        ~GuiRenderer();

        void DrawGUI();

    private:
        const std::string m_glslVersion = "#version 330 core";
        GLFWwindow* m_window;
        ImGuiIO* m_io;
        ImGuiWindowFlags m_windowFlags;
        int m_width, m_height;

        int m_passLength{5};
        char m_username [40]{};
        char m_origin   [40]{};

        FileUtil m_fileUtil;
    };
}

#endif //GUIRENDERER_H
