
#pragma once

#include "../application/application.hpp"


#include <functional>

namespace hid
{
    struct Engine
    {
        Engine();
        ~Engine();
        void setup();
        void run();
        std::unique_ptr<hid::Application> resolveApplication();
        const std::string classLogTag;
        std::unique_ptr<hid::Application> application;
    };
};