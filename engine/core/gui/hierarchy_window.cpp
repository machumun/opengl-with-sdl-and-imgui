#include "hierarchy_window.hpp"
#include "imgui.h"

#include <iostream>

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
    for (auto &object : sceneData->objects)
    {
        // if (ImGui::TreeNodeEx((void *)std::stoi(object->name), ImGuiTreeNodeFlags_Selected, object->name.c_str()))
        // {
        //     // ImGui::SliderFloat("Position", (float *)&transform.position, 10.f, -10.f);
        //     ImGui::TreePop();
        // }
    }
}

void HierarchyWindow::showWindow(bool *open)
{
    ImGui::Begin("Hierarchy", open);
    drawObjects();
    ImGui::End();
}