#pragma once

#include "../../core/wrapper/graphics_wrapper.hpp"

namespace hid
{
    struct VulkanImageView
    {

        VulkanImageView(const vk::Device &device,
                        const vk::Image &image,
                        const vk::Format &format,
                        const vk::ImageAspectFlags &aspectFlags,
                        const uint32_t &mipLevels);

        const vk::ImageView &getImageView() const;

    private:
        const vk::UniqueImageView imageView;
    };
}