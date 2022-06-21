#pragma once

#include "inspector_window.hpp"
#include "hierarchy_window.hpp"

#include "../light_settings.hpp"
#include "../wrapper/glm_wrapper.hpp"
#include "../scene/scene_data.hpp"

#include <memory>
#include <vector>

namespace hid
{

    struct Layout
    {
        bool isActive;
        bool show_another_window;

        float rotateSpeed;

        float delta;

        char text1[64] = "";

        std::vector<hid::assets::GLTF> gltfs;

        std::unique_ptr<hid::InspectorWindow> inspectorWindow;
        std::unique_ptr<hid::HierarchyWindow> hierarchyWindow;

        std::shared_ptr<hid::SceneData> sceneData;

        Layout(std::shared_ptr<hid::SceneData> sceneData)
            : inspectorWindow{std::make_unique<hid::InspectorWindow>()},
              hierarchyWindow{std::make_unique<hid::HierarchyWindow>(sceneData)},
              isActive{true},
              show_another_window{false},
              rotateSpeed{.0f},
              delta{.0f}

        {
        }

        void init();

        // gui entry point
        void viewport();

        void debugWindow(bool *);
        // void hierarchyWindow(bool *);
    };
}