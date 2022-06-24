#pragma once

#include "../wrapper/glm_wrapper.hpp"

namespace hid
{
    struct EnvironmentalSettings
    {
        glm::vec3 ambientColor;
        float ambientIntencity;

        bool postProcessing;

        float bloomStrength;

        float shadowStrength;

        EnvironmentalSettings()
            : ambientColor{glm::vec3(153.f / 255.f, 166.f / 255.f, 180.f / 255.f)},
              ambientIntencity{.583f},
              postProcessing{true},
              bloomStrength{1.f}
        {
        }
    };
}