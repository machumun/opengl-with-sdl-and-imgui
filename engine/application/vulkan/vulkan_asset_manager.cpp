#include "vulkan_asset_manager.hpp"

using hid::VulkanAssetManager;

void VulkanAssetManager::loadAssetManifest(const hid::VulkanPhysicalDevice &physicalDevice,
                                           const hid::VulkanDevice &device,
                                           const std::unique_ptr<hid::VulkanRenderContext> &renderContext,
                                           const hid::AssetManifest &assetManifest)
{
    // TODO: Load everything in the asset manifest.
}

void VulkanAssetManager::reloadContextualAssets(const hid::VulkanPhysicalDevice &physicalDevice,
                                                const hid::VulkanDevice &device,
                                                const std::unique_ptr<hid::VulkanRenderContext> &renderContext)
{
    // TODO: Reload any context sensitive assets that are already cached.
}