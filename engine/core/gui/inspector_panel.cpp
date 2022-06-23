#include "inspector_panel.hpp"
#include "layout.hpp"

#include "../components/mesh_renderer.hpp"

using hid::InspectorPanel;

void InspectorPanel::contents()
{

    // const static std::string logTag{"hid::InspectorPanel"};
    if (layout == nullptr)
    {
        return;
    }

    if (layout->selectedObjectIndex > -1)
    {
        auto &object = layout->sceneData->objects[layout->selectedObjectIndex];
        // auto &object = layout->sceneData->objects[0];
        // std::string s{"foo"};
        ImGui::InputText("name", &object->name);
        for (auto &component : object->components)
        {
            component->inspectorView();
        }

        // if (object->hasComponent<hid::Transform>())
        // {
        //     auto &transform = object->getComponent<Transform>();
        //     if (ImGui::TreeNodeEx((void *)transform.Type, ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
        //     {
        //         ImGui::SliderFloat3("Position", (float *)&transform.position, 10.f, -10.f);
        //         ImGui::SliderFloat3("Scale", (float *)&transform.scale, 10.f, -10.f);
        //         ImGui::TreePop();
        //     }
        // }
    }
}
