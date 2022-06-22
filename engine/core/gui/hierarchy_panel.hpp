#pragma once

#include "../interfaces/interface_panel.hpp"
#include "../scene/scene_data.hpp"

namespace hid
{
    struct HierarchyWindow : public IPanel
    {
        std::shared_ptr<hid::SceneData> sceneData;
        HierarchyWindow(hid::Layout *layout)
            : IPanel("Hierarchy", layout) {}

        void contents() override;
    };
}