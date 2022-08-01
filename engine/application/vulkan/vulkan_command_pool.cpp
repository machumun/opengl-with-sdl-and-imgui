#include "vulkan_command_pool.hpp"

using hid::VulkanCommandPool;

namespace
{
    vk::UniqueCommandPool createCommandPool(const hid::VulkanDevice &device)
    {
        vk::CommandPoolCreateInfo info{
            vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
            device.getGraphicsQueueIndex()};

        return device.getDevice().createCommandPoolUnique(info);
    }

    vk::UniqueCommandBuffer beginCommandBuffer(const vk::CommandPool &commandPool,
                                               const hid::VulkanDevice &device)
    {
        vk::CommandBufferAllocateInfo allocateInfo{
            commandPool,                      // Command pool
            vk::CommandBufferLevel::ePrimary, // Level
            1};                               // Command buffer count

        vk::UniqueCommandBuffer commandBuffer{
            std::move(device.getDevice().allocateCommandBuffersUnique(allocateInfo)[0])};

        vk::CommandBufferBeginInfo beginInfo{
            vk::CommandBufferUsageFlagBits::eOneTimeSubmit, // Flags
            nullptr                                         // Inheritance info
        };

        commandBuffer->begin(beginInfo);

        return commandBuffer;
    }

    void endCommandBuffer(const vk::CommandBuffer &commandBuffer,
                          const hid::VulkanDevice &device)
    {
        commandBuffer.end();

        vk::SubmitInfo submitInfo{
            0,              // Wait semaphore count
            nullptr,        // Wait semaphores
            nullptr,        // Wait destination stage mask
            1,              // Command buffer count
            &commandBuffer, // Command buffers,
            0,              // Signal semaphore count
            nullptr         // Signal semaphores
        };

        device.getGraphicsQueue().submit(1, &submitInfo, vk::Fence());
        device.getGraphicsQueue().waitIdle();
    }

    std::vector<vk::UniqueCommandBuffer> createCommandBuffers(const vk::Device &device,
                                                              const vk::CommandPool &commandPool,
                                                              const uint32_t &count)
    {
        vk::CommandBufferAllocateInfo info{
            commandPool,                      // Command pool
            vk::CommandBufferLevel::ePrimary, // Level
            count                             // Command buffer count
        };

        return device.allocateCommandBuffersUnique(info);
    }
}

VulkanCommandPool::VulkanCommandPool(const hid::VulkanDevice &device)
    : commandPool{::createCommandPool(device)} {}

vk::UniqueCommandBuffer VulkanCommandPool::beginCommandBuffer(const hid::VulkanDevice &device) const
{
    return ::beginCommandBuffer(commandPool.get(), device);
}

void VulkanCommandPool::endCommandBuffer(const vk::CommandBuffer &commandBuffer, const hid::VulkanDevice &device) const
{
    ::endCommandBuffer(commandBuffer, device);
}

std::vector<vk::UniqueCommandBuffer> VulkanCommandPool::createCommandBuffers(const hid::VulkanDevice &device,
                                                                             const uint32_t &count) const
{
    return ::createCommandBuffers(device.getDevice(), commandPool.get(), count);
}