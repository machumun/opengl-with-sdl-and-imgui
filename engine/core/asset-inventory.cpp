#include "asset-inventory.hpp"

std::string hid::assets::resolvePipelinePath(const hid::assets::Pipeline &pipeline)
{
    switch (pipeline)
    {
    case hid::assets::Pipeline::Default:
        return "default";
    case hid::assets::Pipeline::Lit:
        return "lit";

    default:
        return "default";
    }
}

std::string hid::assets::resolveStaticMeshPath(const hid::assets::StaticMesh &staticMesh)
{
    switch (staticMesh)
    {
    case hid::assets::StaticMesh::Crate:
        return "assets/models/crate.obj";
    case hid::assets::StaticMesh::Monkey:
        return "assets/models/monkey.obj";
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
    case hid::assets::Texture::Cube:
        return "assets/textures/cube.png";
    case hid::assets::Texture::Hamster:
        return "assets/textures/hamster.png";
    default:
        return "assets/textures/cube.png";
    }
}
