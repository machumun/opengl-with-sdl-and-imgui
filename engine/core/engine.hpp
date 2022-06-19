
#pragma once
#include "internal-ptr.hpp"

#include "gui/gui.hpp"

#include <functional>

namespace hid
{
    struct Engine
    {
        Engine();
        void init();
        void run();

    private:
        struct Internal;
        hid::internal_ptr<Internal> internal;
    };
};