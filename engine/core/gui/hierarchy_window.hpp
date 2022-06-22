#pragma once

#include "../interfaces/IWindow.hpp"
#include "../object.hpp"
#include "../scene/scene_data.hpp"

namespace hid
{
    struct HierarchyWindow : public IWindow
    {
        std::shared_ptr<hid::SceneData> sceneData;
        HierarchyWindow(std::shared_ptr<hid::SceneData> sceneData)
            : sceneData{sceneData} {}

        void drawObjects();
        void showWindow(bool *open) override;
    };
}