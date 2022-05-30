#pragma once
#include <memory>

namespace hid
{
    struct ImGuiUtils
    {
        void (*registeredUserImGui)();
        void userImGui();
    };
}
