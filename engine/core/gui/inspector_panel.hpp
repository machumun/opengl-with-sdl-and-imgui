#pragma once

#include "../interfaces/interface_panel.hpp"
#include "../scene/scene_data.hpp"

#include "../log.hpp"

namespace hid
{
    struct InspectorPanel : public IPanel
    {

        InspectorPanel(hid::Layout *layout)
            : IPanel("Inspector", layout)
        {
        }

        void contents() override;
    };

}