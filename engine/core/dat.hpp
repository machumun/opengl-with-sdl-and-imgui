#pragma once

#include "imgui.h"
#include "light-settings.hpp"
#include "glm-wrapper.hpp"

#include <memory>

namespace hid
{

    struct Dat
    {
        bool isActive;
        bool show_another_window;

        float rotateSpeed;

        float pointLightStrength;
        glm::vec4 pointLightColor;
        glm::vec3 pointLightPosition;

        float ambientLightStrength;
        glm::vec4 ambientLightColor;

        float gamma;

        bool bloom;

        Dat() : isActive{true},
                show_another_window{false},
                pointLightStrength{float(3.f)},

                pointLightColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),

                pointLightPosition(glm::vec3(1.0f, 1.0f, 1.0f)),

                ambientLightStrength{.25f},

                ambientLightColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),

                rotateSpeed{.0f},

                gamma{2.2f},
                bloom{true}
        {
        }

        void init();

        void userImGui();
    };

}