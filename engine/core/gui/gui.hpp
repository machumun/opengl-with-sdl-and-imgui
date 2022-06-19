#pragma once

#include "imgui.h"
#include "../light-settings.hpp"
#include "../glm-wrapper.hpp"
#include "../object.hpp"

#include <memory>
#include <vector>

namespace hid
{

    struct Gui
    {
        bool isActive;
        bool show_another_window;

        float rotateSpeed;
        hid::LightSettings lightSettings;

        float delta;

        char text1[64] = "";

        // std::vector<std::shared_ptr<hid::StaticMeshInstance>> staticMeshInstances;
        // std::vector<std::shared_ptr<hid::AnimationPlane>> animationPlanes;

        std::vector<std::shared_ptr<hid::Object>> objects;

        std::vector<hid::assets::GLTF> gltfs;

        Gui() : isActive{true},
                show_another_window{false},
                rotateSpeed{.0f},
                lightSettings{
                    hid::Light{
                        hid::LightType::Point,
                        glm::vec3(1.0f, 1.0f, 1.0f),
                        glm::vec3(216.f / 255.f, 218.f / 255.f, 192.f / 255.f),
                        5.093f},
                    hid::Light{
                        LightType::Ambient,
                        glm::vec3(1.0f, 1.0f, 1.0f),
                        glm::vec3(153.f / 255.f, 166.f / 255.f, 180.f / 255.f),
                        .583f}},
                delta{.0f}

        {
        }

        void init();

        void userImGui();

        void debugWindow(bool *);
        void hierarchyWindow(bool *);
    };
}