#include <iostream>

#include "../vendor/imgui.h"
#include "../vendor/backends/imgui_impl_glfw.h"
#include "../vendor/backends/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

int main(){
    if(!glfwInit()){
        std::cerr << "GLFW INIT ERROR\n";
        return -1;
    }

    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(500, 500, "Hello, OpenGL", nullptr, nullptr);
    if(!window){
        std::cerr << "GLFW WINDOW CREATION ERROR\n";
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
    }

    return 0;
}