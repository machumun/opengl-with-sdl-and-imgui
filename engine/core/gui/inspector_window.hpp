#pragma once

#include "../interfaces/IWindow.hpp"
#include "../object.hpp"

namespace hid
{
    struct InspectorWindow : public IWindow
    {
        hid::Object *selectedObject;
        InspectorWindow() : selectedObject{nullptr} {}
        void showWindow(bool *open) override;
        void drawComponents();
    };
}