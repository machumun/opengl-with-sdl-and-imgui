#pragma once

#include "../../core/asset_manager.hpp"
#include "../../core/asset_loader.hpp"

#include "../../core/asset_manifest.hpp"

#include "opengl_mesh.hpp"
#include "opengl_pipeline.hpp"
#include "opengl_texture.hpp"

#include <unordered_map>

namespace hid
{
    struct OpenGLAssetManager : public hid::AssetManager
    {
        OpenGLAssetManager() = default;

        void loadStaticMeshes(const std::vector<std::pair<std::string, std::string>> &staticMeshPairs) override
        {
            for (const auto &staticMesh : staticMeshPairs)
            {
                if (staticMeshCache.count(staticMesh.first) == 0)
                {
                    staticMeshCache.insert(std::make_pair(
                        staticMesh.first,
                        std::make_unique<hid::OpenGLMesh>(hid::assets::loadOBJFile(staticMesh.second))));
                }
            }
        }

        void loadTextures(const std::vector<std::pair<std::string, std::string>> &texturePairs) override
        {
            for (const auto &texture : texturePairs)
            {
                if (textureCache.count(texture.first) == 0)
                {
                    textureCache.insert(std::pair(
                        texture.first,
                        std::make_unique<hid::OpenGLTexture>(hid::assets::loadBitmap(texture.second))));
                }
            }
        }

        void loadShaders(const std::vector<std::pair<std::string, std::pair<std::string, std::string>>> &shaderPairs) override
        {
            static const std::string logTag{"hid::OpenGLAssetManager::loadShader"};
            for (const auto &shaderKey : shaderPairs)
            {
                const std::string key = shaderKey.first;
                const std::string vert = shaderKey.second.first;
                const std::string frag = shaderKey.second.second;

                if (shaderCache.count(key) == 0)
                {
                    shaderCache.insert(std::pair(
                        key,
                        std::make_unique<hid::OpenGLShader>(vert, frag)));
                }
                else
                {
                    hid::log(logTag, "This shader has already been loaded.");
                }
            }
        }

        void loadAssetManifest(const hid::AssetManifest &assetManifest)
        {
            loadStaticMeshes(assetManifest.staticMeshs);
            loadTextures(assetManifest.textures);
            loadShaders(assetManifest.shaders);
        }

        hid::StaticMesh *getStaticMesh(const std::string &staticMesh) const override
        {
            return staticMeshCache.at(staticMesh).get();
        }

        hid::Texture *getTexture(const std::string &texture) const override
        {
            return textureCache.at(texture).get();
        }

        hid::Shader *getShader(const std::string &shader) const override
        {
            return shaderCache.at(shader).get();
        }

    private:
        std::unordered_map<std::string, std::unique_ptr<hid::OpenGLMesh>> staticMeshCache;
        std::unordered_map<std::string, std::unique_ptr<hid::OpenGLTexture>> textureCache;
        std::unordered_map<std::string, std::unique_ptr<hid::OpenGLShader>> shaderCache;
    };
}