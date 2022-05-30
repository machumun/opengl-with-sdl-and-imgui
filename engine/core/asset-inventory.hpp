#pragma once

#include <string>

namespace hid::assets
{

    enum class Pipeline
    {
        DefaultPass,
        LitPass,
        BlurPass
    };

    enum class StaticMesh
    {
        Crate,
        Monkey,
        Hamster,
        Plane
    };

    enum class Texture
    {
        Cube,
        Hamster,
    };

    std::pair<std::string, std::string> resolvePipelinePath(const hid::assets::Pipeline &pipeline);
    std::string resolveStaticMeshPath(const hid::assets::StaticMesh &staticMesh);
    std::string resolveTexturePath(const hid::assets::Texture &texture);
}