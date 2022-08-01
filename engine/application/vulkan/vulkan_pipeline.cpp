#include "vulkan_pipeline.hpp"

#include "vulkan_application.hpp"

using hid::VulkanApplication;
using hid::VulkanPipeline;

namespace
{
    vk::UniqueDescriptorSetLayout createDescripterSetLayout(const hid::VulkanDevice &device)
    {
        vk::DescriptorSetLayoutBinding textureBinding{
            0,                                         // Binding
            vk::DescriptorType::eCombinedImageSampler, // Descriptor type
            1,                                         // Descriptor count
            vk::ShaderStageFlagBits::eFragment,        // Shader stage flags
            nullptr};                                  // Immutable samplers

        vk::DescriptorSetLayoutCreateInfo info{
            vk::DescriptorSetLayoutCreateFlags(), // Flags
            1,                                    // Binding count
            &textureBinding};                     // Bindings

        return device.getDevice().createDescriptorSetLayoutUnique(info);
    }

    vk::UniquePipelineLayout createPipelineLayout(const hid::VulkanDevice &device,
                                                  const vk::DescriptorSetLayout &descriptorSetLayout)
    {
        // TODO: Implement me.
    }

    vk::UniquePipeline createPipeline(const hid::VulkanPhysicalDevice &physicalDevice,
                                      const hid::VulkanDevice &device,
                                      const vk::PipelineLayout &pipelineLayout,
                                      const std::string &shaderName,
                                      const vk::Viewport &viewport,
                                      const vk::Rect2D &scissor,
                                      const vk::RenderPass &renderPass)
    {
        // TODO: Implement me.
    }
}

VulkanPipeline::VulkanPipeline(const hid::VulkanPhysicalDevice &physicalDevice,
                               const hid::VulkanDevice &device,
                               const std::string &shaderName,
                               const vk::Viewport &viewport,
                               const vk::Rect2D &scissor,
                               const vk::RenderPass &renderPass)
    : descriptorSetLayout{::createDescripterSetLayout(device)},
      pipelineLayout{::createPipelineLayout(device, descriptorSetLayout.get())},
      pipeline{::createPipeline(
          physicalDevice,
          device,
          pipelineLayout.get(),
          shaderName,
          viewport,
          scissor,
          renderPass)} {}

void VulkanPipeline::render()
{
    VulkanApplication::vulkanAssetManager;
}