#include "asset_inventory.hpp"

std::pair<std::string, std::string> hid::assets::resolvePipelinePath(const hid::assets::Pipeline &pipeline)
{
    switch (pipeline)
    {
    case hid::assets::Pipeline::DefaultPass:
        return {"default", "default"};
    case hid::assets::Pipeline::LitPass:
        return {"lit", "lit"};
    case hid::assets::Pipeline::BlurPass:
        return {"lit", "blur"};
    default:
        return {"default", "default"};
    }
}

std::string hid::assets::resolveGLTFModelPath(const hid::assets::GLTF &gltf)
{
    switch (gltf)
    {
    case hid::assets::GLTF::TestBox:
        return "assets/gltfs/testbox_reverse/gltftest.gltf";
    default:
        return "assets/gltfs/testbox_reverse/gltftest.gltf";
    }
}
