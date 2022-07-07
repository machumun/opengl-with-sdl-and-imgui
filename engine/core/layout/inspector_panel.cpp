#include "inspector_panel.hpp"
#include "layout.hpp"
#include "../log.hpp"
#include "../components/mesh_renderer.hpp"

using hid::InspectorPanel;

void InspectorPanel::contents()
{

    // const static std::string logTag{"hid::InspectorPanel"};
    if (layout == nullptr)
    {
        return;
    }

    if (layout->selectedObject == nullptr)
    {
        return;
    }

    ImGui::InputText("name", &layout->selectedObject->name);
    ImGui::Checkbox("isActive", &layout->selectedObject->isActive);
    for (auto &component : layout->selectedObject->components)
    {
        component->inspector();
    }
}
