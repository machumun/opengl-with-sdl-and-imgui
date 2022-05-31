#pragma once

#include "asset-inventory.hpp"
#include "glm-wrapper.hpp"
#include "graphics-wrapper.hpp"

#include <memory>

namespace hid
{
    enum class LightType
    {
        Point,
        Ambient,
        Directional
    };

    struct Light
    {
        LightType type;
        glm::vec3 position;
        glm::vec4 color;
        float strength;
        Light(
            const LightType &type,
            const glm::vec3 &position = glm::vec3{1.0f, 1.0f, 1.0f},
            const glm::vec4 &color = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f},
            const float &strength = 1.0f)
            : position(position),
              color(color),
              strength(strength),
              type(type){};

        void setPosition(const glm::vec3 &_position) { position = _position; }
        void setColor(const glm::vec4 &_color) { color = _color; }
        void setStrength(float &_strength) { strength = _strength; }
    };

    struct LightSettings
    {

        Light pointLight;
        Light ambientLight;
        float gamma;
        bool bloom;

        LightSettings(const Light &pointLight, const Light &ambientLight)
            : pointLight{pointLight},
              ambientLight{ambientLight},
              gamma{2.2},
              bloom{false}
        {
        }

        ~LightSettings()
        {
        }
    };
}