// utilsはユーザーの為の便利関数セットとする
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
