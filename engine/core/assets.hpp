#pragma once

#include "mesh.hpp"
#include "bitmap.hpp"
#include <string>


namespace hid::assets
{
    std::string loadTextFile(const std::string &path);
    hid::Mesh loadOBJFile(const std::string &path);
    hid::Bitmap loadBitmap(const std::string &path);
}