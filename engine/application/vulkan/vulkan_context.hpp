#pragma once

#include "vulkan_physical_device.hpp"
#include "vulkan_surface.hpp"
#include "vulkan_device.hpp"
#include "vulkan_render_context.hpp"
#include "vulkan_command_pool.hpp"

#include "vulkan_asset_manager.hpp"

#include "../../core/sdl_window.hpp"
#include "../../core/wrapper/graphics_wrapper.hpp"

#include "../../core/renderer.hpp"

namespace hid
{
    struct VulkanContext : public hid::Renderer
    {
        VulkanContext();

        const void render() const override;
        void setup(std::shared_ptr<hid::SceneData> sceneData) override;

        bool renderBegin();
        void renderEnd();
        void recreateRenderContext();

    private:
        const vk::UniqueInstance instance;
        const VulkanPhysicalDevice physicalDevice;
        const hid::SDLWindow window;
        const hid::VulkanSurface surface;
        const hid::VulkanDevice device;
        const hid::VulkanCommandPool commandPool;

        // hid::VulkanRenderContext renderContext;

        std::unique_ptr<hid::VulkanRenderContext> renderContext;
    };
}