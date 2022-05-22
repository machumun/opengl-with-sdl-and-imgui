#pragma once

#include <string>

namespace hid::assets
{

    enum class Pipeline
    {
        Default,
        Lit
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

    std::string resolvePipelinePath(const hid::assets::Pipeline &pipeline);
    std::string resolveStaticMeshPath(const hid::assets::StaticMesh &staticMesh);
    std::string resolveTexturePath(const hid::assets::Texture &texture);
}