#pragma once

#include "../interfaces/interface_panel.hpp"
#include "../scene/scene_data.hpp"

namespace hid
{
    struct InspectorWindow : public IPanel
    {
        std::shared_ptr<hid::SceneData> sceneData;
        InspectorWindow(hid::Layout *layout)
            : IPanel("Inspector", layout) {}
        void contents() override;
    };
}