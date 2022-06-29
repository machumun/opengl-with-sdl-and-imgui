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
        std::string titleString;
        const char *title;
        hid::Layout *layout;

        IPanel(const std::string &title, hid::Layout *layout)
            : titleString{title},
              title{titleString.c_str()},
              layout{layout}
        {
        }

        ~IPanel() = default;

        virtual void contents() = 0;

        // void setParentWindow(hid::IPanel *window)
        // {
        //     parent = window;
        // }

        void showWindow(bool *open)
        {
            ImGui::Begin(title, open);
            contents();
            ImGui::End();
        }

        void showWindowWithNoPadding(bool *open)
        {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
            ImGui::Begin(title, open);
            contents();
            ImGui::End();
            ImGui::PopStyleVar();
        }
    };
}