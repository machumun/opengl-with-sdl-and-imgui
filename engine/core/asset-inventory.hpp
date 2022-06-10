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
        LightSaber,
        Hamster,
        Plane
    };

    enum class Texture
    {

        Bomb,
        Hamster,
        Metal,
        Empty,
        Frog
    };

    enum class GLTF
    {
        Scene
    };

    std::pair<std::string, std::string> resolvePipelinePath(const hid::assets::Pipeline &pipeline);
    std::string resolveStaticMeshPath(const hid::assets::StaticMesh &staticMesh);
    std::string resolveTexturePath(const hid::assets::Texture &texture);
    std::string resolveGLTFModelPath(const hid::assets::GLTF &gltf);
}