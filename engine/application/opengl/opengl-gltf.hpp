#pragma once

#include <map>
#include "../../core/gltf.hpp"

namespace hid
{

    struct OpenGLGLTF
    {
        hid::GLTF model;
        OpenGLGLTF(const hid::GLTF &model) : model{model}
        {
        }
    };
}