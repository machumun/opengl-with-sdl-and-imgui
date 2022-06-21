#pragma once

#include <functional>

// template method patern
namespace hid
{
    struct Application
    {
        Application();

        virtual ~Application() = default;

        void startApplication();
        bool runMainLoop();
        float timeStep();

        virtual void init() = 0;

        virtual void update(const float &delta) = 0;
        virtual void render() = 0;

    private:
        const float performanceFrequency;
        uint64_t currentTime;
        uint64_t previousTime;
    };
}