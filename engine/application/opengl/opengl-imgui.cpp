#include "opengl-imgui.hpp"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

// #include "../../core/sdl-wrapper.hpp"
#include "../../utils/imgui-utils.hpp"
#include <string>
#include <iostream>

using hid::OpenGLGui;

struct OpenGLGui::Internal
{
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char *glsl_version = "#version 100";
#elif defined(__APPLE__)
    // GL 3.2 Core + GLSL 150
    const char *glsl_version = "#version 150";
#else
    // GL 3.3 + GLSL 330
    const char *glsl_version = "#version 330";
#endif

    Internal(SDL_Window *window, SDL_GLContext context) : userImGui(nullptr)
    {
        setup(window, context);
    }


    std::function<void()> userImGui;
    void setup(SDL_Window *window, SDL_GLContext context)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO &io = ImGui::GetIO();
        (void)io;

        ImGui::StyleColorsDark();

        ImGui_ImplSDL2_InitForOpenGL(window, context);
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    void loopImGui(SDL_Window *window)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();


        if (!(userImGui == nullptr))
        {
            userImGui();
        }
    }

    void cleanUpImGui()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void render()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void setUserImGui(std::function<void()> fp)
    {
        userImGui = fp;
    }
};

OpenGLGui::OpenGLGui(SDL_Window *window, SDL_GLContext context) : internal(hid::make_internal_ptr<Internal>(window, context)) {}

void OpenGLGui::setup(SDL_Window *window, SDL_GLContext context)
{
    internal->setup(window, context);
}

void OpenGLGui::loopImGui(SDL_Window *window)
{
    internal->loopImGui(window);
}

void OpenGLGui::cleanUpImGui()
{
    internal->cleanUpImGui();
}

void OpenGLGui::render()
{
    internal->render();
}

void OpenGLGui::setUserImGui(std::function<void()> fp)
{
    internal->setUserImGui(fp);
}