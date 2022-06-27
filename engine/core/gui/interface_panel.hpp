#pragma once

#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

#include <memory>
#include <string>

namespace hid
{
    struct Layout;

    struct IPanel
    {
        std::string title;
        hid::Layout *layout;

        IPanel(const std::string &title, hid::Layout *layout)
            : title{title},
              layout{layout} {}

        ~IPanel() = default;

        virtual void contents() = 0;

        // void setParentWindow(hid::IPanel *window)
        // {
        //     parent = window;
        // }

        void showWindow(bool *open)
        {
            // if (layout != nullptr)
            // {
            //     return;
            // }
            ImGui::Begin(title.c_str(), open);
            contents();
            ImGui::End();
        }

        void showWindowWithNoPadding(bool *open)
        {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
            ImGui::Begin(title.c_str(), open);
            contents();
            ImGui::End();
            ImGui::PopStyleVar();
        }
    };
}