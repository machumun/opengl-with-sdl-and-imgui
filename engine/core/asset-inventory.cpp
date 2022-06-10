#include "asset-inventory.hpp"

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

std::string hid::assets::resolveStaticMeshPath(const hid::assets::StaticMesh &staticMesh)
{
    switch (staticMesh)
    {
    case hid::assets::StaticMesh::Crate:
        return "assets/models/crate.obj";
    case hid::assets::StaticMesh::LightSaber:
        return "assets/models/lightsaber.obj";
    case hid::assets::StaticMesh::Hamster:
        return "assets/models/hamster.obj";
    case hid::assets::StaticMesh::Plane:
        return "assets/models/plane.obj";
    default:
        return "assets/models/crate.obj";
    }
}

std::string hid::assets::resolveTexturePath(const hid::assets::Texture &texture)
{
    switch (texture)
    {
    case hid::assets::Texture::Bomb:
        return "assets/textures/bomb.png";
    case hid::assets::Texture::Frog:
        return "assets/textures/chara.png";
    case hid::assets::Texture::Hamster:
        return "assets/textures/hamster.png";
    case hid::assets::Texture::Metal:
        return "assets/textures/metal.png";
    case hid::assets::Texture::Empty:
        return "assets/textures/empty.png";
    default:
        return "assets/textures/empty.png";
    }
}

std::string hid::assets::resolveGLTFModelPath(const hid::assets::GLTF &gltf)
{
    switch (gltf)
    {
    case hid::assets::GLTF::Scene:
        return "assets/gltfs/farm-sim/scene.gltf";
    default:
        return "assets/models/scene.gltf";
    }
}
