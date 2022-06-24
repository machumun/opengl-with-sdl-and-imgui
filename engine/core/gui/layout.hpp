#pragma once
#include "inspector_panel.hpp"
#include "hierarchy_panel.hpp"
#include "environmental_settings_panel.hpp"

#include "../scene/scene_data.hpp"

#include "imgui.h"

#include <memory>
#include <vector>

namespace hid
{

    struct Layout
    {
        std::shared_ptr<hid::SceneData> sceneData;
        int32_t selectedObjectIndex;

        bool showInspector = true;
        bool showHierarchy = true;
        bool showEnvironmentalSettings = true;

        std::unique_ptr<hid::InspectorPanel> inspectorPanel;
        std::unique_ptr<hid::HierarchyPanel> hierarchyPanel;
        std::unique_ptr<hid::EnvironmentalSettingsPanel> environmentalSettingsPanel;

        bool isActive;
        bool show_another_window;
        uint32_t counter;
        float rotateSpeed;

        float delta;

        char text1[64] = "";

        // std::vector<hid::assets::GLTF> gltfs;

        Layout(std::shared_ptr<hid::SceneData> &sceneData)
            : selectedObjectIndex{-1},
              counter{0},
              sceneData{sceneData},
              showInspector{true},
              showHierarchy{true},
              inspectorPanel{std::make_unique<hid::InspectorPanel>(this)},
              hierarchyPanel{std::make_unique<hid::HierarchyPanel>(this)},
              environmentalSettingsPanel{std::make_unique<hid::EnvironmentalSettingsPanel>(this)},
              isActive{true},
              show_another_window{false},
              rotateSpeed{.0f},
              delta{.0f}
        {
        }

        void debugWindow(bool *);

        // gui entry point
        void viewport();
    };
}