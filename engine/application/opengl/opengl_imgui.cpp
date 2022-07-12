#include "opengl_imgui.hpp"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

#include <string>
#include <iostream>

using hid::OpenGLImGui;

OpenGLImGui::OpenGLImGui()
    : viewport(nullptr)
{
}

void OpenGLImGui::setup(SDL_Window *window, SDL_GLContext context)
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

    // ImGui::StyleColorsLight();

    // ImGuiStyle &style = ImGui::GetStyle();
    // style.Alpha = .3f;

    // ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1.f, 1.f, 1.f, .3f));

    static ImGuiColorEditFlags alpha_flags = ImGuiColorEditFlags_AlphaPreview;
}

void OpenGLImGui::update(SDL_Window *window)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();

    if (viewport != nullptr)
    {
        viewport();
    }
}

void OpenGLImGui::cleanUp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void OpenGLImGui::render()
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

void OpenGLImGui::setViewport(std::function<void()> fp)
{
    viewport = fp;
}
