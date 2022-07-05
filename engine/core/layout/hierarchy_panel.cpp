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

    for (auto &object : layout->sceneData->objects)
    {
        treeNode(object.get(), base_flags);
    }

    // uint32_t objectsSize = layout->sceneData->objects.size();
    // for (uint32_t i = 0; i < objectsSize; ++i)
    // {
    //     ImGuiTreeNodeFlags node_flags = base_flags;
    //     if (layout->selectedObjectIndex == i)
    //     {
    //         node_flags |= ImGuiTreeNodeFlags_Selected;
    //     }

    //     if (ImGui::TreeNodeEx((void *)(intptr_t)i, node_flags, layout->sceneData->objects[i]->name.c_str()))
    //     {
    //         // ImGui::PushID(i);

    //         // ImGui::PopID();

    //         ImGui::TreePop();
    //     }
    //     if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
    //     {
    //         layout->selectedObjectIndex = i;
    //     }
    // }
}

void HierarchyPanel::treeNode(hid::Object *object, const ImGuiTreeNodeFlags &flags)
{
    ImGuiTreeNodeFlags node_flags = flags;
    if (layout->selectedObject != nullptr && object == layout->selectedObject)
    {
        node_flags |= ImGuiTreeNodeFlags_Selected;
    }

    if (object->children.size() == 0)
    {
        node_flags |= ImGuiTreeNodeFlags_Leaf;
    }

    if (ImGui::TreeNodeEx((void *)(intptr_t)(&object->id), node_flags, object->name.c_str()))
    {
        // ImGui::PushID(i);
        if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
        {
            layout->selectedObject = object;
        }

        for (auto &child : object->children)
        {
            treeNode(child.get(), flags);
        }
        // ImGui::PopID();

        ImGui::TreePop();
    }
}