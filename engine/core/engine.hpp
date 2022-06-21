
#pragma once

#include "../application/application.hpp"
#include "../application/opengl/opengl-application.hpp"
#include "gui/gui.hpp"

#include <functional>

namespace hid
{
    struct Engine
    {
        Engine();
        ~Engine();
        void init();
        void run();
        std::unique_ptr<hid::Application> resolveApplication();
        const std::string classLogTag;
        std::unique_ptr<hid::Application> application;
    };
};