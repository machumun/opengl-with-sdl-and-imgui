#pragma once

#include "../interfaces/IComponent.hpp"

namespace hid
{
    struct SceneHierarchyPanel
    {
        void drawComponents(hid::IComponent *);
    };
}