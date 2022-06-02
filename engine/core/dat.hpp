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
        hid::LightSettings lightSettings;

        Dat() : isActive{true},
                show_another_window{false},
                rotateSpeed{.0f},
                lightSettings{
                    hid::Light{
                        hid::LightType::Point,
                        glm::vec3(1.0f, 1.0f, 1.0f),
                        glm::vec3(216.f / 255.f, 218.f / 255.f, 192.f / 255.f),
                        6.893f},
                    hid::Light{
                        LightType::Ambient,
                        glm::vec3(1.0f, 1.0f, 1.0f),
                        glm::vec3(153.f / 255.f, 166.f / 255.f, 180.f / 255.f),
                        .583f}}
        {
        }

        void init();

        void userImGui();
    };

}