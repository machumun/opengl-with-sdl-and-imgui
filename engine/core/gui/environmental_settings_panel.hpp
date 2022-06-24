#pragma once

#include "interface_panel.hpp"
#include "../scene/scene_data.hpp"

namespace hid
{
    struct EnvironmentalSettingsPanel : public IPanel
    {
        EnvironmentalSettingsPanel(hid::Layout *layout)
            : IPanel("Environment Settings", layout) {}

        void contents() override;
    };
}