#include "vulkan_asset_manager.hpp"
#include "../../core/log.hpp"

using hid::VulkanAssetManager;
namespace
{

    hid::VulkanPipeline createPipeline(const std::string &shaderName,
                                       const hid::VulkanPhysicalDevice &physicalDevice,
                                       const hid::VulkanDevice &device,
                                       const hid::VulkanRenderContext &renderContext)
    {
        // const std::string pipelinePath{shadername};
        const static std::string logTag{"hid::VulkanAssetManager::createPipeline"};

        hid::log(logTag, "Creating pipeline:" + shaderName);

        return hid::VulkanPipeline(physicalDevice,
                                   device,
                                   shaderName,
                                   renderContext.getViewport(),
                                   renderContext.getScissor(),
                                   renderContext.getRenderPass());
    }
}

void VulkanAssetManager::loadAssetManifest(const hid::VulkanPhysicalDevice &physicalDevice,
                                           const hid::VulkanDevice &device,
                                           const std::unique_ptr<hid::VulkanRenderContext> &renderContext,
                                           const hid::AssetManifest &assetManifest)
{
    for (const auto &shader : assetManifest.shaders)
    {
        // if ()
        // {
        // }
    }
}

void VulkanAssetManager::reloadContextualAssets(const hid::VulkanPhysicalDevice &physicalDevice,
                                                const hid::VulkanDevice &device,
                                                const std::unique_ptr<hid::VulkanRenderContext> &renderContext)
{
    // TODO
}