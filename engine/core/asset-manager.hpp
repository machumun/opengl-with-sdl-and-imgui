#pragma once

#include "asset-inventory.hpp"
#include <vector>

namespace hid
{
    struct AssetManager
    {
        virtual void loadPipelines(const std::vector<hid::assets::Pipeline> &pipelines) = 0;

        virtual void loadStaticMeshes(const std::vector<hid::assets::StaticMesh> &staticMeshes) = 0;

        virtual void loadTextures(const std::vector<hid::assets::Texture> &textures) = 0;
    };
}