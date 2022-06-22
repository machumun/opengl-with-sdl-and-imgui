#pragma once
#include "inspector_panel.hpp"
#include "hierarchy_panel.hpp"

#include "../scene/scene_data.hpp"

#include "imgui.h"

#include <memory>
#include <vector>

namespace hid
{

    struct Layout
    {
        std::shared_ptr<hid::SceneData> sceneData;

        std::unique_ptr<hid::InspectorWindow> inspectorWindow;
        std::unique_ptr<hid::HierarchyWindow> hierarchyWindow;

        bool isActive;
        bool show_another_window;
        uint32_t counter;
        float rotateSpeed;

        float delta;

        char text1[64] = "";

        // std::vector<hid::assets::GLTF> gltfs;

        Layout(std::shared_ptr<hid::SceneData> &sceneData)
            : counter{0},
              sceneData{sceneData},
              inspectorWindow{std::make_unique<hid::InspectorWindow>(this)},
              hierarchyWindow{std::make_unique<hid::HierarchyWindow>(this)},
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