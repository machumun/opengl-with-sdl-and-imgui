#pragma once

#include "wrapper/glm_wrapper.hpp"

namespace hid
{
    enum MaterialFlag
    {
        RECEIVE_SHADOWS = 1 << 0,
        SPECULAR_HIGHLIGHTS = 1 << 1,
        SUBTRACTIVE_MIXED_LIGHTING = 1 << 2,
        SPECULAR_SETUP = 1 << 3
    };

    struct Material
    {
        std::string shader;

        std::string albedo;
        std::string normal;
        std::string metaric;
        std::string speculer;

        glm::vec3 baseColor;

        uint32_t materialFlags;

        bool alphaBlend;

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
              speculer{speculer},
              materialFlags{0},
              alphaBlend{false}
        {
        }

        void setBaseColor(const glm::vec3 &color)
        {
            baseColor = color;
        };
    };
}