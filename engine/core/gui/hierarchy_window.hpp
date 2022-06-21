#pragma once

#include "../interfaces/IWindow.hpp"
#include "../object.hpp"

namespace hid
{
    struct HierarchyWindow : public IWindow
    {
        void drawObjects(const std::vector<hid::Object> &objects);
        void showWindow(bool *open) override;
    };
}