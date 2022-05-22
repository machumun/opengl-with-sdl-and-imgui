#pragma once

#include "imgui.h"
#include "light-settings.hpp"
#include "glm-wrapper.hpp"

#include <memory>

namespace hid
{
    struct Vec4
    {
        float x, y, z, w;
        // ImVec4 imVec4;
        // glm::vec4 glmVec4;

        Vec4() : x(float(1.0f)), y(float(1.0f)), z(float(1.0f)), w(float(1.0f)){};
    };

    // struct Position
    // {
    //     float r, g, b, a;
    //     Color() : r(float(1.0f)), g(float(1.0f)), b(float(1.0f)), a(float(1.0f)){};
    // };

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

        Dat() : isActive(false),
                show_another_window(false),
                pointLightStrength(float(.5f)),

                pointLightColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),

                pointLightPosition(glm::vec3(1.0f, 1.0f, 1.0f)),

                ambientLightStrength(float(.5f)),

                ambientLightColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),

                rotateSpeed(float(.0f))
        {
        }

        void init();

        void userImGui();
    };

}