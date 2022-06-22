#pragma once

#include "imgui.h"

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

        virtual void contents() {}

        // void setParentWindow(hid::IPanel *window)
        // {
        //     parent = window;
        // }

        void showWindow(bool *open)
        {
            ImGui::Begin(title.c_str(), open);
            contents();
            ImGui::End();
        }
    };
}