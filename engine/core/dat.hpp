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

        Dat() : isActive(true),
                show_another_window(false),
                pointLightStrength(float(0.714f)),

                pointLightColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),

                pointLightPosition(glm::vec3(1.0f, 1.0f, 1.0f)),

                ambientLightStrength(float(.073f)),

                ambientLightColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),

                rotateSpeed(float(.0f))
        {
        }

        void init();

        void userImGui();
    };

}