#include "layout.hpp"
#include "../log.hpp"

#include <nfd.h>

#include <string>
#include <iostream>

using hid::Layout;

void Layout::debugWindow(bool *p_open)
{
    ImGui::Begin("SandBox Window", p_open);
    ImGui::Checkbox("Is Active", &isActive); // Edit bools storing our window open/close state

    ImGui::SliderFloat("rotate speed", &rotateSpeed, 0.0f, 100.0f); // Edit 1 float using a slider from 0.0f to 1.0f
    // if (ImGui::TreeNode("point light"))
    // {
    //     ImGui::SliderFloat("intensity", &lightSettings.pointLight.intensity, 0.0f, 10.0f);
    //     ImGui::SliderFloat3("position", (float *)&lightSettings.pointLight.position, -10.0f, 10.0f);
    //     ImGui::ColorEdit3("color", (float *)&lightSettings.pointLight.color);
    //     ImGui::TreePop();
    // }

    // if (ImGui::TreeNode("ambient light"))
    // {
    //     ImGui::SliderFloat("intensity", &lightSettings.ambientLight.intensity, 0.0f, 10.0f);
    //     ImGui::ColorEdit3("color", (float *)&lightSettings.ambientLight.color);
    //     ImGui::TreePop();
    // }
    // ImGui::Checkbox("Bloom", &lightSettings.bloom);
    // ImGui::SliderFloat("blur intensity", &lightSettings.bloomIntensity, 0.0f, 10.0f);

    if (ImGui::Button("Button"))
    {
        counter++;
    }

    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("delta between frames %.3f", &delta);

    ImGui::InputText("textbox 1", text1, sizeof(text1));

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::End();
}

void Layout::viewport()
{
    static const std::string logTag{"hid::Layout::viewport"};
    static bool dockSpaceOpen = true;
    static bool opt_fullscreen = true;
    static bool opt_padding = false;

    static bool showDebug = true;

    static bool showDemoWindow = true;

    static bool showInspector = true;
    static bool showHierarchy = true;
    static bool showEnvironmentalSettings = true;
    static bool showGameView = true;

    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &dockSpaceOpen, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO &io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::MenuItem("(demo menu)", NULL, false, false);
            if (ImGui::MenuItem("New"))
            {
            }
            if (ImGui::MenuItem("Open", "Ctrl+O"))
            {
            }
            if (ImGui::BeginMenu("Open Recent"))
            {
                ImGui::MenuItem("fish_hat.c");
                ImGui::MenuItem("fish_hat.inl");
                ImGui::MenuItem("fish_hat.h");
                if (ImGui::BeginMenu("More.."))
                {
                    ImGui::MenuItem("Hello");
                    ImGui::MenuItem("Sailor");
                    if (ImGui::BeginMenu("Recurse.."))
                    {
                        // ShowExampleMenuFile();
                        ImGui::EndMenu();
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("Save", "Ctrl+S"))
            {

                nfdchar_t *outPath = new nfdchar_t;
                nfdresult_t result = NFD_OpenDialog("png,jpg;pdf", NULL, &outPath);
                if (result == NFD_OKAY)
                {
                    // hid::log(logTag, "NFD::Open" + outPath);
                    std::cout << outPath << std::endl;
                    delete outPath;
                }
                // do error handling

                if (ImGui::MenuItem("Save", "CTRL+S"))
                { /* do something */
                }

                // ImGui::EndMenu();
            }
            if (ImGui::MenuItem("Save As.."))
            {
            }

            ImGui::Separator();

            if (ImGui::BeginMenu("Docking"))
            {
                static bool enabled = true;
                ImGui::MenuItem("Enabled", "", &enabled);
                ImGui::BeginChild("child", ImVec2(0, 60), true);
                for (int i = 0; i < 10; i++)
                    ImGui::Text("Scrolling Text %d", i);
                ImGui::EndChild();
                static float f = 0.5f;
                static int n = 0;
                ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
                ImGui::InputFloat("Input", &f, 0.1f);
                ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Colors"))
            {
                float sz = ImGui::GetTextLineHeight();
                for (int i = 0; i < ImGuiCol_COUNT; i++)
                {
                    const char *name = ImGui::GetStyleColorName((ImGuiCol)i);
                    ImVec2 p = ImGui::GetCursorScreenPos();
                    ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
                    ImGui::Dummy(ImVec2(sz, sz));
                    ImGui::SameLine();
                    ImGui::MenuItem(name);
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Options")) // <-- Append!
            {
                static bool b = true;
                ImGui::Checkbox("SomeOption", &b);
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Disabled", false)) // Disabled
            {
                IM_ASSERT(0);
            }
            if (ImGui::MenuItem("Checked", NULL, true))
            {
            }
            if (ImGui::MenuItem("Quit", "Alt+F4"))
            {
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z"))
            {
            }
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false))
            {
            } // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X"))
            {
            }
            if (ImGui::MenuItem("Copy", "CTRL+C"))
            {
            }
            if (ImGui::MenuItem("Paste", "CTRL+V"))
            {
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Options"))
        {
            // Disabling fullscreen would allow the window to be moved to the front of other windows,
            // which we can't undo at the moment without finer window depth/z control.
            ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
            ImGui::MenuItem("Padding", NULL, &opt_padding);
            ImGui::Separator();

            if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0))
            {
                dockspace_flags ^= ImGuiDockNodeFlags_NoSplit;
            }
            if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0))
            {
                dockspace_flags ^= ImGuiDockNodeFlags_NoResize;
            }
            if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0))
            {
                dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode;
            }
            if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))
            {
                dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar;
            }
            if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen))
            {
                dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode;
            }
            ImGui::Separator();

            if (ImGui::MenuItem("Close", NULL, false))
                dockSpaceOpen = false;
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    debugWindow(&showDebug);

    hierarchyPanel->showWindow(&showHierarchy);
    inspectorPanel->showWindow(&showInspector);
    environmentalSettingsPanel->showWindow(&showEnvironmentalSettings);
    gameViewPanel->showWindowWithNoPadding(&showGameView);

    ImGui::ShowDemoWindow(&showDemoWindow);

    ImGui::End();
}