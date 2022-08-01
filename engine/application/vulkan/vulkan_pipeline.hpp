#pragma once

#include "../../core/wrapper/graphics_wrapper.hpp"

#include "vulkan_device.hpp"
#include "vulkan_physical_device.hpp"

#include <string>
#include <vector>

namespace hid
{
    struct VulkanAssetManager;

    struct VulkanPipeline
    {
        VulkanPipeline(const hid::VulkanPhysicalDevice &physicalDevice,
                       const hid::VulkanDevice &device,
                       const std::string &shaderName,
                       const vk::Viewport &viewport,
                       const vk::Rect2D &scissor,
                       const vk::RenderPass &renderPass);

        void render();

    private:
        const vk::UniqueDescriptorSetLayout descriptorSetLayout;
        const vk::UniquePipelineLayout pipelineLayout;
        const vk::UniquePipeline pipeline;
    };
}