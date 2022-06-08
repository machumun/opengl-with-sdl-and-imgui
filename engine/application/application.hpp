#pragma once

#include "../core/internal-ptr.hpp"
#include "../core/dat.hpp"
#include <functional>

// template method
namespace hid
{
    struct Application
    {
        Application();

        virtual ~Application() = default;

        void startApplication();

        bool runMainLoop();

        virtual void init() = 0;

        virtual void update(const float &delta) = 0;
        virtual void render() = 0;

    private:
        struct Internal;
        hid::internal_ptr<Internal> internal;
    };
}