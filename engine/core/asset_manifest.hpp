#pragma once

#include "asset_loader.hpp"
#include <vector>

namespace hid
{
    struct AssetManifest
    {
        std::vector<std::pair<std::string, std::string>> staticMeshs;
        std::vector<std::pair<std::string, std::string>> textures;
        std::vector<std::pair<std::string, std::pair<std::string, std::string>>> shaders;
    };
}