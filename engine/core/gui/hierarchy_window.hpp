#pragma once

#include "../interfaces/IWindow.hpp"
#include "../object.hpp"
#include "../scene/scene_data.hpp"

namespace hid
{
    struct HierarchyWindow : public IWindow
    {

        HierarchyWindow() = default;

        void drawObjects();
        void showWindow(bool *open) override;
    };
}