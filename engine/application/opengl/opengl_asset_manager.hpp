#pragma once

#include "../../core/asset_manager.hpp"
#include "../../core/asset_loader.hpp"

#include "opengl_mesh.hpp"
#include "opengl_pipeline.hpp"
#include "opengl_texture.hpp"
#include "opengl_gltf.hpp"

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
                        hid::OpenGLMesh(hid::assets::loadOBJFile(staticMesh.second))));
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
                        hid::OpenGLTexture(hid::assets::loadBitmap(texture.second))));
                }
            }
        }

        void loadGLTFModels(const std::vector<hid::assets::GLTF> &gltfs) override
        {
            for (const auto &gltf : gltfs)
            {
                hid::OpenGLGLTF openglGLTF = hid::OpenGLGLTF(hid::assets::loadGLTF(hid::assets::resolveGLTFModelPath(gltf)));
                // loadTextures(openglGLTF.gltf.textures);

                if (gltfCache.count(gltf) == 0)
                {
                    gltfCache.insert(std::pair(
                        gltf,
                        &openglGLTF));
                }
            }
        }

        void loadShader(const std::string &key, const std::pair<std::string, std::string> &shader) override
        {
            static const std::string logTag{"hid::OpenGLAssetManager::loadShader"};
            if (shaderCache.count(key) == 0)
            {
                shaderCache.insert(std::pair(
                    key,
                    hid::OpenGLShader(shader.first, shader.second)));
            }
            else
            {
                hid::log(logTag, "This shader has already been loaded.");
            }
        }

        const hid::OpenGLMesh &getStaticMesh(const std::string &staticMesh) const
        {
            return staticMeshCache.at(staticMesh);
        }

        const hid::OpenGLTexture &getTexture(const std::string &texture) const
        {
            return textureCache.at(texture);
        }

        const hid::OpenGLGLTF *getGLTF(const hid::assets::GLTF &gltf) const
        {
            return gltfCache.at(gltf);
        }

    private:
        std::unordered_map<std::string, hid::OpenGLMesh> staticMeshCache;
        std::unordered_map<std::string, hid::OpenGLTexture> textureCache;
        std::unordered_map<std::string, hid::OpenGLShader> shaderCache;

        std::unordered_map<hid::assets::GLTF, hid::OpenGLGLTF *> gltfCache;
    };
}