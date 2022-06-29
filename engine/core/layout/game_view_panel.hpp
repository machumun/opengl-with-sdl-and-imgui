#pragma once

#include "interface_panel.hpp"
#include "../scene/scene_data.hpp"

namespace hid
{
    struct GameViewPanel : public IPanel
    {
        int textureId;
        GameViewPanel(hid::Layout *layout)
            : textureId{1},
              IPanel("Game View (16 : 10)", layout) {}

        void contents() override;
    };
}