#include "inspector-window.hpp"
#include "imgui.h"

#include "../interfaces/IComponent.hpp"

using hid::InspectorWindow;

void InspectorWindow::drawComponents()
{
    if (selectedObject != nullptr)
    {
        if (selectedObject->hasComponent<hid::Transform>())
        {
            auto &transform = selectedObject->getComponent<Transform>();
            if (ImGui::TreeNodeEx((void *)transform.Type, ImGuiTreeNodeFlags_Selected, "Transform"))
            {
                ImGui::SliderFloat("Position", (float *)&transform.position, 10.f, -10.f);
                ImGui::TreePop();
            }
        }
    }
}

void InspectorWindow::showWindow(bool *open)
{
    ImGui::Begin("Inspector", open);
    drawComponents();
    ImGui::End();
}