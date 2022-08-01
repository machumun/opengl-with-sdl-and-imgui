#pragma once

#include "../core/asset_manager.hpp"
#include "../core/file_manager.hpp"
#include "../core/input_manager.hpp"
#include "../core/scene_manager.hpp"

#include "../core/time.hpp"

#include "../core/layout/layout.hpp"

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
        static float timeStep();

        virtual void setup() = 0;

        virtual void start() = 0;
        virtual void update() = 0;
        virtual void render() = 0;

        // for singletong
        static hid::AssetManager *assetManager;
        static std::unique_ptr<hid::FileManager> fileManager;
        static std::unique_ptr<hid::InputManager> inputManager;
        static std::unique_ptr<hid::SceneManager> sceneManager;
        // static;
        // static std::unique_ptr<hid::Time> time;

        static std::unique_ptr<hid::Scene> currentScene;
        static std::unique_ptr<hid::Layout> layout;

    private:
        static const float performanceFrequency;
        static uint64_t currentTime;
        static uint64_t previousTime;
    };
}