#pragma once

#include "environmental_settings.hpp"

#include "../object.hpp"
#include "../wrapper/glm_wrapper.hpp"

namespace hid
{
    struct SceneData
    {
        std::vector<std::shared_ptr<hid::Object>> objects;
        std::unique_ptr<hid::EnvironmentalSettings> environmentalSettings;
        // std::pair<uint32_t, uint32_t> gameViewSize;
        SceneData()
            : environmentalSettings{std::make_unique<hid::EnvironmentalSettings>()} {}
    };
}