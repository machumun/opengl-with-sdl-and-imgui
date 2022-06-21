#pragma once

#include "../object.hpp"
#include "../light_settings.hpp"
#include "../wrapper/glm_wrapper.hpp"

namespace hid
{
    struct SceneData
    {
        std::vector<std::unique_ptr<hid::Object>> objects;
        hid::LightSettings lightSettings;

        SceneData() : lightSettings{
                          hid::Light{
                              hid::LightType::Point,
                              glm::vec3(1.0f, 1.0f, 1.0f),
                              glm::vec3(216.f / 255.f, 218.f / 255.f, 192.f / 255.f),
                              5.093f},
                          hid::Light{
                              LightType::Ambient,
                              glm::vec3(1.0f, 1.0f, 1.0f),
                              glm::vec3(153.f / 255.f, 166.f / 255.f, 180.f / 255.f),
                              .583f}} {}
    };
}