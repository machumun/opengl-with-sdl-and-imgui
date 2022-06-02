#pragma once

#include "../core/asset-inventory.hpp"
#include "../core/glm-wrapper.hpp"
#include "../core/internal-ptr.hpp"

namespace hid
{
    enum class MaterialType
    {
        UnLit,
        Lit
    };

    struct Material
    {
        hid::assets::Texture albedo;
        hid::assets::Texture normal;
        hid::assets::Texture metaric;
        hid::assets::Texture speculer;

        glm::vec3 baseColor;

        Material(const hid::assets::Texture &albedo = hid::assets::Texture::Empty,
                 const glm::vec3 &baseColor = glm::vec3{1.0f, 1.0f, 1.0f},
                 const hid::assets::Texture &normal = hid::assets::Texture::Empty,
                 const hid::assets::Texture &metaric = hid::assets::Texture::Empty,
                 const hid::assets::Texture &speculer = hid::assets::Texture::Empty)
            : albedo{albedo},
              baseColor{baseColor},
              normal(normal),
              metaric(metaric),
              speculer(speculer)
        {
        }
    };
}