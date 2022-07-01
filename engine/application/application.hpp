#pragma once

#include "../../core/asset_manager.hpp"
#include <memory>

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

        virtual void setup() = 0;

        virtual void start() = 0;
        virtual void update(const float &delta) = 0;
        virtual void render() = 0;

        // for singletong
        static std::unique_ptr<hid::AssetManager> assetManager;

    private:
        const float performanceFrequency;
        uint64_t currentTime;
        uint64_t previousTime;
    };
}