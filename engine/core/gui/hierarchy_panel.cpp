#include "hierarchy_panel.hpp"
#include "layout.hpp"

using hid::HierarchyWindow;

void HierarchyWindow::contents()
{
    uint32_t i = 0;
    // parent;
    if (layout != nullptr)
    {
        for (auto &object : layout->sceneData->objects)
        {
            if (ImGui::TreeNodeEx((void *)(intptr_t)i, 0, object->name.c_str()))
            {
                // ImGui::PushID(i);
                // if (ImGui::Selectable())
                // {
                // }
                // ImGui::SliderFloat("Position", (float *)&transform.position, 10.f, -10.f);
                ImGui::TreePop();
            }
            ++i;
        }
    }
}
