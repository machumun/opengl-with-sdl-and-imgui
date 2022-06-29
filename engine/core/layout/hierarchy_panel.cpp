#include "hierarchy_panel.hpp"
#include "layout.hpp"

#include "../log.hpp"

#include <iostream>

using hid::HierarchyPanel;

void HierarchyPanel::contents()
{
    static std::string logTag{"hid::Hierarchy::contents"};
    static ImGuiTreeNodeFlags base_flags =
        ImGuiTreeNodeFlags_OpenOnArrow |
        ImGuiTreeNodeFlags_OpenOnDoubleClick |
        ImGuiTreeNodeFlags_SpanAvailWidth;

    // parent;
    if (layout == nullptr)
    {
        return;
    }

    uint32_t objectsSize = layout->sceneData->objects.size();
    for (uint32_t i = 0; i < objectsSize; ++i)
    {
        ImGuiTreeNodeFlags node_flags = base_flags;
        if (layout->selectedObjectIndex == i)
        {
            node_flags |= ImGuiTreeNodeFlags_Selected;
        }

        if (ImGui::TreeNodeEx((void *)(intptr_t)i, node_flags, layout->sceneData->objects[i]->name.c_str()))
        {
            ImGui::PushID(i);

            ImGui::PopID();
            ImGui::TreePop();
        }
        if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
        {
            layout->selectedObjectIndex = i;
        }
    }
}
