#include "opengl-imgui.hpp"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

// #include "../../core/sdl-wrapper.hpp"
#include "../../utils/imgui-utils.hpp"
#include <string>
#include <iostream>

using hid::OpenGLImGui;

struct OpenGLImGui::Internal
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

    std::function<void()> userImGui;

    Internal()
        : userImGui(nullptr)
    {
    }

    void setup(SDL_Window *window, SDL_GLContext context)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        (void)io;

        // ImGui::StyleColorsDark();

        ImGui_ImplSDL2_InitForOpenGL(window, context);
        ImGui_ImplOpenGL3_Init(glsl_version);

        ImGui::StyleColorsLight();
    }

    void loop(SDL_Window *window)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        if (!(userImGui == nullptr))
        {
            userImGui();
        }
    }

    void cleanUp()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void render()
    {
        ImGuiIO &io = ImGui::GetIO();
        std::pair<uint32_t, uint32_t> displaySize = hid::sdl::getDisplaySize();
        io.DisplaySize = ImVec2(displaySize.first, displaySize.second);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            SDL_GLContext backupContext = SDL_GL_GetCurrentContext();
            SDL_Window *backupWindow = SDL_GL_GetCurrentWindow();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backupWindow, backupContext);
        }
    }

    void setUserImGui(std::function<void()> fp)
    {
        userImGui = fp;
    }
};

OpenGLImGui::OpenGLImGui() : internal(hid::make_internal_ptr<Internal>()) {}

void OpenGLImGui::setup(SDL_Window *window, SDL_GLContext context)
{
    internal->setup(window, context);
}

void OpenGLImGui::loop(SDL_Window *window)
{
    internal->loop(window);
}

void OpenGLImGui::cleanUp()
{
    internal->cleanUp();
}

void OpenGLImGui::render()
{
    internal->render();
}

void OpenGLImGui::setUserImGui(std::function<void()> fp)
{
    internal->setUserImGui(fp);
}