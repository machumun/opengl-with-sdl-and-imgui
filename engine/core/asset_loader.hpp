#pragma once

#include "mesh.hpp"
#include "bitmap.hpp"
#include "gltf.hpp"

#include <string>
#include <vector>

namespace hid::assets
{
    std::string loadTextFile(const std::string &path, const std::string &mode = "r");
    hid::Mesh loadOBJFile(const std::string &path);
    hid::Bitmap loadBitmap(const std::string &path);
    std::vector<char> loadBinaryFile(const std::string &path);

    // hid::GLTF loadGLTF(const std::string &path);
}