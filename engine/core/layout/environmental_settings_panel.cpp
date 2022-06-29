#include "environmental_settings_panel.hpp"
#include "layout.hpp"

#include "../log.hpp"

#include <iostream>

using hid::EnvironmentalSettingsPanel;

void EnvironmentalSettingsPanel::contents()
{
    // parent;
    if (layout == nullptr)
    {
        return;
    }
    static std::string logTag{"hid::Environment::contents"};
    static ImGuiTreeNodeFlags base_flags =
        ImGuiTreeNodeFlags_OpenOnArrow |
        ImGuiTreeNodeFlags_OpenOnDoubleClick |
        ImGuiTreeNodeFlags_SpanAvailWidth;

    ImGui::Checkbox("Post Processing", &layout->sceneData->environmentalSettings->postProcessing);
    ImGui::SliderFloat("Bloom Threshold", &layout->sceneData->environmentalSettings->bloomThreshold, .0f, 1.f);
    ImGui::ColorPicker3("Ambient Color", &layout->sceneData->environmentalSettings->ambientColor[0]);
    ImGui::DragFloat("Ambient Intencity", &layout->sceneData->environmentalSettings->ambientIntencity);
}
