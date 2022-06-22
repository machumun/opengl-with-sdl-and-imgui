#include "inspector_panel.hpp"

#include "../interfaces/interface_component.hpp"

using hid::InspectorWindow;

void InspectorWindow::contents()
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
}
