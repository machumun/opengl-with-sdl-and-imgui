#pragma once

#include <memory>

namespace hid
{
    struct IWindow
    {
        IWindow() = default;
        ~IWindow() = default;
        std::unique_ptr<hid::IWindow> parent;
        void setParentWindow(hid::IWindow *window)
        {
            parent = std::make_unique<hid::IWindow>(window);
        }
        virtual void showWindow(bool *open) {}
    };
}