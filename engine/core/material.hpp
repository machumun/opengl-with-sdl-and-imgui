#pragma once

#include "asset-inventory.hpp"
#include "glm-wrapper.hpp"
#include "internal-ptr.hpp"

namespace hid
{
    enum class MaterialType
    {
        UnLit,
        Lit
    };

    struct Material
    {
        std::string albedo;
        std::string normal;
        std::string metaric;
        std::string speculer;

        glm::vec3 baseColor;

        Material(const std::string &albedo = "empty",
                 const glm::vec3 &baseColor = glm::vec3{1.0f, 1.0f, 1.0f},
                 const std::string &normal = "empty",
                 const std::string &metaric = "empty",
                 const std::string &speculer = "empty")
            : albedo{albedo},
              baseColor{baseColor},
              normal(normal),
              metaric(metaric),
              speculer(speculer)
        {
        }
    };
}