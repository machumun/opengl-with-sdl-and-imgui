#pragma once

#include "environmental_settings.hpp"
#include "../asset_manager.hpp"

#include "../wrapper/glm_wrapper.hpp"

#include "../object.hpp"

namespace hid
{
    struct SceneData
    {
        std::vector<std::unique_ptr<hid::Object>> objects;
        std::unique_ptr<hid::EnvironmentalSettings> environmentalSettings;
        // std::pair<uint32_t, uint32_t> gameViewSize;
        SceneData()
            : environmentalSettings{std::make_unique<hid::EnvironmentalSettings>()} {}
    };
}