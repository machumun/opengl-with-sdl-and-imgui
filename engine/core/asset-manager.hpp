#pragma once

#include "asset_inventory.hpp"
#include <vector>
#include <utility>

namespace hid
{
    struct AssetManager
    {
        virtual void loadPipelines(const std::vector<hid::assets::Pipeline> &pipelines) = 0;

        virtual void loadStaticMeshes(const std::vector<std::pair<std::string, std::string>> &staticMeshPairs) = 0;

        virtual void loadTextures(const std::vector<std::pair<std::string, std::string>> &texturePairs) = 0;

        virtual void loadGLTFModels(const std::vector<hid::assets::GLTF> &gltfs) = 0;
    };
}