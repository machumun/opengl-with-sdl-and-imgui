#include "hierarchy_window.hpp"
#include "imgui.h"

using hid::HierarchyWindow;

void HierarchyWindow::drawObjects()
{
    // if (selectedObject != nullptr)
    // {
    //     if (selectedObject->hasComponent<hid::Transform>())
    //     {
    //         auto &transform = selectedObject->getComponent<Transform>();
    //         if (ImGui::TreeNodeEx((void *)transform.Type, ImGuiTreeNodeFlags_Selected, "Transform"))
    //         {
    //             ImGui::SliderFloat("Position", (float *)&transform.position, 10.f, -10.f);
    //             ImGui::TreePop();
    //         }
    //     }
    // }
    uint32_t i = 0;
    for (auto &object : parent->sceneData->objects)
    {
        if (ImGui::TreeNodeEx((void *)i, ImGuiTreeNodeFlags_Selected, object->name.c_str()))
        {
            // ImGui::SliderFloat("Position", (float *)&transform.position, 10.f, -10.f);
            ImGui::TreePop();
        }
        ++i;
    }
}

void HierarchyWindow::showWindow(bool *open)
{
    ImGui::Begin("Hierarchy", open);
    drawObjects();
    ImGui::End();
}