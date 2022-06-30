#pragma once

#include "asset_inventory.hpp"
#include <vector>
#include <utility>

namespace hid
{
    struct AssetManager
    {
        virtual void loadStaticMeshes(const std::vector<std::pair<std::string, std::string>> &staticMeshPairs) = 0;

        virtual void loadTextures(const std::vector<std::pair<std::string, std::string>> &texturePairs) = 0;

        virtual void loadGLTFModels(const std::vector<hid::assets::GLTF> &gltfs) = 0;

        virtual void loadShader(const std::string &key, const std::pair<std::string, std::string> &shader) = 0;
    };
}