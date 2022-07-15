#pragma once

#include "../application.hpp"
#include "vulkan_context.hpp"
#include "../../core/wrapper/graphics_wrapper.hpp"
#include "../../core/wrapper/sdl_wrapper.hpp"

namespace hid
{
    struct VulkanApplication : public hid::Application
    {
        VulkanApplication();

        ~VulkanApplication()
        {
            if (window)
            {
                SDL_DestroyWindow(window);
            }
        }

        void start() override;
        void update() override;
        void render() override;
        void setup() override;

    private:
        const hid::VulkanContext context;
        SDL_Window *window;
    };
}

// Application();

// virtual ~Application() = default;

// void startApplication();
// bool runMainLoop();
// static float timeStep();

// virtual void setup() = 0;

// virtual void start() = 0;
// virtual void update() = 0;
// virtual void render() = 0;

// // for singletong
// static std::unique_ptr<hid::AssetManager> assetManager;
// static std::unique_ptr<hid::FileManager> fileManager;
// static std::unique_ptr<hid::InputManager> inputManager;
// static std::unique_ptr<hid::SceneManager> sceneManager;
// // static;
// // static std::unique_ptr<hid::Time> time;

// static std::unique_ptr<hid::Scene> currentScene;
// static std::unique_ptr<hid::Layout> layout;

// private:
// static const float performanceFrequency;
// static uint64_t currentTime;
// static uint64_t previousTime;