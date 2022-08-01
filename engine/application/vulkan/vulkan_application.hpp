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
            // if (window)
            // {
            //     SDL_DestroyWindow(window);
            // }
        }

        void start() override;
        void update() override;
        void render() override;
        void setup() override;

        static std::unique_ptr<hid::VulkanAssetManager> vulkanAssetManager;

    private:
        hid::VulkanContext context;
    };
}
