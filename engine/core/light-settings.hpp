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
        glm::vec3 color;
        float intensity;
        Light(
            const LightType &type,
            const glm::vec3 &position = glm::vec3{1.0f, 1.0f, 1.0f},
            const glm::vec3 &color = glm::vec3{1.0f, 1.0f, 1.0f},
            const float &intensity = 1.0f)
            : position(position),
              color(color),
              intensity(intensity),
              type(type){};

        void setPosition(const glm::vec3 &_position) { position = _position; }
        void setColor(const glm::vec3 &_color) { color = _color; }
        void setIntensity(float &_intensity) { intensity = _intensity; }
    };

    struct LightSettings
    {

        Light pointLight;
        Light ambientLight;
        float bloomIntensity;
        bool bloom;

        LightSettings(const Light &pointLight = Light(LightType::Point),
                      const Light &ambientLight = Light(LightType::Ambient))
            : pointLight{pointLight},
              ambientLight{ambientLight},
              bloomIntensity{0.6},
              bloom{true}
        {
        }

        ~LightSettings()
        {
        }
    };
}