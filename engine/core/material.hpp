#pragma once

#include "wrapper/glm_wrapper.hpp"

namespace hid
{
    enum class MaterialType
    {
        UnLit,
        Lit
    };

    struct Material
    {
        std::string shader;

        std::string albedo;
        std::string normal;
        std::string metaric;
        std::string speculer;

        glm::vec3 baseColor;

        Material(const std::string &shader = "lit",
                 const std::string &albedo = "empty",
                 const glm::vec3 &baseColor = glm::vec3{1.0f, 1.0f, 1.0f},
                 const std::string &normal = "empty",
                 const std::string &metaric = "empty",
                 const std::string &speculer = "empty")
            : shader{shader},
              albedo{albedo},
              baseColor{baseColor},
              normal{normal},
              metaric{metaric},
              speculer{speculer}
        {
        }

        void setBaseColor(const glm::vec3 &color)
        {
            baseColor = color;
        };
    };
}