#ifndef APPLICATION_H
#define APPLICATION_H

#include <cstdint>
#include <memory>
#include <string>

#include <GLFW/glfw3.h>

#include "GuiRenderer.h"

namespace App{
    struct AppSpecs{
        std::string title;
        uint32_t width;
        uint32_t height;
    };

    class Application {
    public:
        explicit Application(AppSpecs  specs);
        ~Application();

        void Loop();

    private:
        AppSpecs m_specs;

        int32_t m_framebufferWidth{0};
        int32_t m_framebufferHeight{0};

        GLFWwindow* m_window{nullptr};
        std::unique_ptr<GuiRenderer> m_gui{nullptr};
    };
}

#endif //APPLICATION_H
