#pragma once

#include "../../core/asset_manager.hpp"

namespace hid
{
    struct VulkanAssetManager : public hid::AssetManager
    {
        VulkanAssetManager();

        void loadStaticMeshes(const std::vector<std::pair<std::string, std::string>> &staticMeshPair) override;
        void loadTextures(const std::vector<std::pair<std::string, std::string>> &texturePairs) override;
        void loadShader(const std::string &key, const std::pair<std::string, std::string> &shader) override
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

        // hid::StaticMesh *getStaticMesh(const std::string &staticMesh) const override
        // {
        //     return staticMeshCache.at(staticMesh).get();
        // }

        // hid::Texture *getTexture(const std::string &texture) const override
        // {
        //     return textureCache.at(texture).get();
        // }

        // hid::Shader *getShader(const std::string &shader) const override
        // {
        //     return shaderCache.at(shader).get();
        // }
    };
}