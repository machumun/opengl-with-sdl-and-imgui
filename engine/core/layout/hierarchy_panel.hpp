#pragma once

#include "interface_panel.hpp"
#include "../scene/scene_data.hpp"

namespace hid
{
    struct HierarchyPanel : public IPanel
    {
        HierarchyPanel(hid::Layout *layout)
            : IPanel("Hierarchy", layout) {}

        void contents() override;

        void treeNode(hid::Object *object, const ImGuiTreeNodeFlags &flags);
    };
}