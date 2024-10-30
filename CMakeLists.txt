cmake_minimum_required(VERSION 3.28)
project(ISOP) # Navn på projekt og exe

# libgcc_s_seh-1.dll + libstdc++-6.dll missing

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -Wextra -Wconversion")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_EXE_LINKER_FLAGS "-static")

include(FetchContent)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG)
if(NOT glfw3_FOUND)
    FetchContent_Declare(
            glfw
            GIT_REPOSITORY https://github.com/glfw/glfw
            GIT_PROGRESS TRUE
    )

    FetchContent_MakeAvailable(glfw)
endif()

set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/extern/imgui")
set(IMGUI_BACKEND_DIR "${CMAKE_SOURCE_DIR}/extern/imgui/backends")

file(GLOB_RECURSE SRC "src/*.cpp")
file(GLOB IMGUI_SRC
    "${IMGUI_DIR}/*.cpp"
    "${IMGUI_BACKEND_DIR}/imgui_impl_opengl3.cpp"
    "${IMGUI_BACKEND_DIR}/imgui_impl_glfw.cpp"
)
file(GLOB IMGUI_INC
    "${IMGUI_DIR}/*.h"
    "${IMGUI_BACKEND_DIR}/imgui_impl_opengl3.h"
    "${IMGUI_BACKEND_DIR}/imgui_impl_glfw.h"
)

add_executable(${PROJECT_NAME} ${SRC} ${IMGUI_SRC}
        src/FileUtil.cpp
        src/FileUtil.h)

target_link_libraries(${PROJECT_NAME}
        PRIVATE glfw
        PRIVATE ${OPENGL_LIBRARIES}
        PRIVATE opengl32
)

target_include_directories(${PROJECT_NAME}
        PRIVATE "${CMAKE_SOURCE_DIR}/extern"
        PRIVATE "${IMGUI_DIR}"
        PRIVATE "${IMGUI_BACKEND_DIR}"
        PRIVATE "${OPENGL_INCLUDE_DIR}"
)