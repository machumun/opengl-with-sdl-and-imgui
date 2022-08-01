#include "vulkan_image.hpp"

using hid::VulkanImage;

namespace
{
    vk::UniqueImage createImage(const vk::Device &device,
                                const uint32_t &width,
                                const uint32_t &height,
                                const uint32_t &mipLevels,
                                const vk::SampleCountFlagBits &sampleCount,
                                const vk::Format &format,
                                const vk::ImageTiling &tiling,
                                const vk::ImageUsageFlags &usageFlags)
    {
        vk::Extent3D extent{
            width,  // Width
            height, // Height
            1       // Depth
        };

        vk::ImageCreateInfo imageInfo{
            vk::ImageCreateFlags(),       // Flags
            vk::ImageType::e2D,           // Image type
            format,                       // Format
            extent,                       // Extent
            mipLevels,                    // Mip levels
            1,                            // Array layers
            sampleCount,                  // Sample count
            tiling,                       // Tiling
            usageFlags,                   // Usage flags
            vk::SharingMode::eExclusive,  // Sharing mode
            0,                            // Queue family index count
            nullptr,                      // Queue family indices,
            vk::ImageLayout::eUndefined}; // Initial layout

        return device.createImageUnique(imageInfo);
    }

    vk::UniqueDeviceMemory allocateImageMemory(const hid::VulkanPhysicalDevice &physicalDevice,
                                               const vk::Device &device,
                                               const vk::Image &image,
                                               const vk::MemoryPropertyFlags &memoryFlags)
    {
        vk::MemoryRequirements memoryRequirements{device.getImageMemoryRequirements(image)};

        uint32_t memoryTypeIndex{physicalDevice.getMemoryTypeIndex(memoryRequirements.memoryTypeBits, memoryFlags)};

        vk::MemoryAllocateInfo info{
            memoryRequirements.size, // Allocation size
            memoryTypeIndex};        // Memory type index

        vk::UniqueDeviceMemory deviceMemory{device.allocateMemoryUnique(info)};

        device.bindImageMemory(image, deviceMemory.get(), 0);

        return deviceMemory;
    }

    void applyTransitionLayoutCommand(const hid::VulkanDevice &device,
                                      const hid::VulkanCommandPool &commandPool,
                                      const vk::PipelineStageFlags &sourceStageFlags,
                                      const vk::PipelineStageFlags &destinationStageFlags,
                                      const vk::ImageMemoryBarrier &barrier)
    {

        vk::UniqueCommandBuffer commandBuffer{commandPool.beginCommandBuffer(device)};

        commandBuffer->pipelineBarrier(
            sourceStageFlags,
            destinationStageFlags,
            vk::DependencyFlags(),
            0, nullptr,
            0, nullptr,
            1, &barrier);

        commandPool.endCommandBuffer(commandBuffer.get(), device);
    }

    void transitionLayout(const hid::VulkanDevice &device,
                          const hid::VulkanCommandPool &commandPool,
                          const vk::Image &image,
                          const vk::Format &format,
                          const uint32_t &mipLevels,
                          const vk::ImageLayout &oldLayout,
                          const vk::ImageLayout &newLayout)
    {
        vk::ImageMemoryBarrier barrier;
        barrier.image = image;
        barrier.oldLayout = oldLayout;
        barrier.newLayout = newLayout;
        barrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
        barrier.subresourceRange.baseMipLevel = 0;
        barrier.subresourceRange.levelCount = mipLevels;
        barrier.subresourceRange.baseArrayLayer = 0;
        barrier.subresourceRange.layerCount = 1;

        if (oldLayout == vk::ImageLayout::eUndefined && newLayout == vk::ImageLayout::eColorAttachmentOptimal)
        {
            barrier.dstAccessMask = vk::AccessFlagBits::eDepthStencilAttachmentRead | vk::AccessFlagBits::eDepthStencilAttachmentWrite;
            barrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eDepth;

            return ::applyTransitionLayoutCommand(device,
                                                  commandPool,
                                                  vk::PipelineStageFlagBits::eTopOfPipe,
                                                  vk::PipelineStageFlagBits::eEarlyFragmentTests,
                                                  barrier);
        }

        throw std::runtime_error("hid::VulkanImage::transitionLayout: Unsupported 'old' and 'new' image layout combination.");
    }

}

VulkanImage::VulkanImage(const hid::VulkanCommandPool &commandPool,
                         const hid::VulkanPhysicalDevice &physicalDevice,
                         const hid::VulkanDevice &device,
                         const uint32_t &width,
                         const uint32_t &height,
                         const uint32_t &mipLevels,
                         const vk::SampleCountFlagBits &sampleCount,
                         const vk::Format &format,
                         const vk::ImageTiling &tiling,
                         const vk::ImageUsageFlags &usageFlags,
                         const vk::MemoryPropertyFlags &memoryFlags,
                         const vk::ImageLayout &oldLayout,
                         const vk::ImageLayout &newLayout)
    : width{width},
      height{height},
      mipLevels{mipLevels},
      format{format},
      image{::createImage(device.getDevice(),
                          width,
                          height,
                          mipLevels,
                          sampleCount,
                          format,
                          tiling,
                          usageFlags)},
      imageMemory{::allocateImageMemory(physicalDevice,
                                        device.getDevice(),
                                        image.get(),
                                        memoryFlags)} {}

uint32_t VulkanImage::getWidth() const
{
    return width;
}

uint32_t VulkanImage::getHeight() const
{
    return height;
}

uint32_t VulkanImage::getMipLevels() const
{
    return mipLevels;
}

const vk::Format &VulkanImage::getFormat() const
{
    return format;
}

const vk::Image &VulkanImage::getImage() const
{
    return image.get();
}