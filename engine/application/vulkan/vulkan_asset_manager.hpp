#pragma once

#include "vulkan_physical_device.hpp"
#include "vulkan_device.hpp"
#include "vulkan_render_context.hpp"
#include "vulkan_pipeline.hpp"

#include <unordered_map>

#include "../../core/asset_manager.hpp"

namespace hid
{
    struct VulkanAssetManager : public hid::AssetManager
    {
        // VulkanAssetManager();

        void loadStaticMeshes(const std::vector<std::pair<std::string, std::string>> &staticMeshPair) override {}
        void loadTextures(const std::vector<std::pair<std::string, std::string>> &texturePairs) override {}
        void loadShaders(const std::vector<std::pair<std::string, std::pair<std::string, std::string>>> &shaderPairs) override
        {
            // static const std::string logTag{"hid::OpenGLAssetManager::loadShader"};
            // if (shaderCache.count(key) == 0)
            // {
            //     shaderCache.insert(std::pair(
            //         key,
            //         std::make_unique<hid::OpenGLShader>(shader.first, shader.second)));
            // }
            // else
            // {
            //     hid::log(logTag, "This shader has already been loaded.");
            // }
        }

        void loadAssetManifest(const hid::VulkanPhysicalDevice &physicalDevice,
                               const hid::VulkanDevice &device,
                               const std::unique_ptr<hid::VulkanRenderContext> &renderContext,
                               const hid::AssetManifest &assetManifest);

        void reloadContextualAssets(const hid::VulkanPhysicalDevice &physicalDevice,
                                    const hid::VulkanDevice &device,
                                    const std::unique_ptr<hid::VulkanRenderContext> &renderContext);

        hid::StaticMesh *getStaticMesh(const std::string &staticMesh) const override
        {
            // return staticMeshCache.at(staticMesh).get();
            return nullptr;
        }

        hid::Texture *getTexture(const std::string &texture) const override
        {
            // return textureCache.at(texture).get();
            return nullptr;
        }

        hid::Shader *getShader(const std::string &shader) const override
        {
            // return shaderCache.at(shader).get();
            return nullptr;
        }
        
        private:
        std
    };
}