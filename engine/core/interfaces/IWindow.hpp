#pragma once

namespace hid
{

    struct IWindow
    {
        IWindow() = default;
        ~IWindow() = default;
        virtual void showWindow(bool *open) = 0;
    };
}