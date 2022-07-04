#pragma once

#include "interface_panel.hpp"
#include "../scene/scene_data.hpp"

namespace hid
{
    struct GameViewPanel : public IPanel
    {
        static int textureId;
        static bool isWindowFocused;
        static bool isWindowHovered;
        static ImVec2 viewportBounds[2];

        GameViewPanel(hid::Layout *layout)
            : IPanel("Game View (16 : 10)", layout) {}

        void contents() override;
    };
}