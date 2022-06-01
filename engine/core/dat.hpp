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

        float pointLightIntensity;
        glm::vec3 pointLightColor;
        glm::vec3 pointLightPosition;

        float ambientLightIntensity;
        glm::vec3 ambientLightColor;

        float bloomIntensity;

        bool bloom;

        Dat() : isActive{true},
                show_another_window{false},
                pointLightIntensity{float(6.893f)},

                pointLightColor(glm::vec3(216.f / 255.f, 218.f / 255.f, 192.f / 255.f)),

                pointLightPosition(glm::vec3(1.0f, 1.0f, 1.0f)),

                ambientLightIntensity{.583f},

                ambientLightColor(glm::vec3(153.f / 255.f, 166.f / 255.f, 180.f / 255.f)),

                rotateSpeed{.0f},

                bloomIntensity{0.3f},
                bloom{true}
        {
        }

        void init();

        void userImGui();
    };

}