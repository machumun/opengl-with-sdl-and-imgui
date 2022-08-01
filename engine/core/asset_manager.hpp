#pragma once

#include "shader.hpp"
#include "texture.hpp"
#include "static_mesh.hpp"

#include "asset_manifest.hpp"

#include <string>
#include <vector>
#include <utility>

namespace hid
{
    struct AssetManager
    {
        virtual void loadStaticMeshes(const std::vector<std::pair<std::string, std::string>> &staticMeshPairs) = 0;

        virtual void loadTextures(const std::vector<std::pair<std::string, std::string>> &texturePairs) = 0;

        // virtual void loadGLTFModels(const std::vector<hid::assets::GLTF> &gltfs) = 0;

        // virtual void loadShaders(const std::string &key, const std::pair<std::string, std::string> &shader) = 0;
        virtual void loadShaders(const std::vector<std::pair<std::string, std::pair<std::string, std::string>>> &shaderPairs) = 0;

        // virtual void loadAssetManifest(const hid::AssetManifest &assetManifest) = 0;

        virtual hid::Shader *getShader(const std::string &shader) const = 0;
        virtual hid::Texture *getTexture(const std::string &texture) const = 0;
        virtual hid::StaticMesh *getStaticMesh(const std::string &staticMesh) const = 0;

        void loadStandardStaticMeshes();
    };
}