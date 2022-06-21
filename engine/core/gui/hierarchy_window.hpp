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
        void drawObjects(const std::vector<hid::Object> &objects);
        void showWindow(bool *open) override;
    };
}