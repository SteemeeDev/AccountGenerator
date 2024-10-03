#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>

#include "../vendor/imgui.h"
#include "../vendor/backends/imgui_impl_glfw.h"
#include "../vendor/backends/imgui_impl_opengl3.h"

#include "GuiRenderer.h"

#define GL_SILENCE_DEPRECATION
#include "GLFW/glfw3.h"

namespace App{
    struct AppSpecifications{
        std::string title;
        uint32_t width;
        uint32_t height;
    };

    class Application{
    public:
        Application(const AppSpecifications& specs);
        ~Application();

        void Loop();

        [[nodiscard]] GLFWwindow* GetWindow() const {return m_window;}

    private:
        AppSpecifications m_specs;

        uint32_t m_framebufferW;
        uint32_t m_framebufferH;

        GLFWwindow* m_window{nullptr};
        std::unique_ptr<GuiRenderer> m_gui{nullptr};
    };
}


#endif //APPLICATION_H
