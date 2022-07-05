#pragma once

#include "environmental_settings.hpp"
#include "../asset_manager.hpp"

#include "../wrapper/glm_wrapper.hpp"

#include "../object.hpp"

#include <unordered_map>

namespace hid
{
    struct SceneData
    {
        std::vector<std::unique_ptr<hid::Object>> objects;
        // std::unordered_map<uint32_t, hid::Object *> objectsMap;
        std::unique_ptr<hid::EnvironmentalSettings> environmentalSettings;
        SceneData()
            : environmentalSettings{std::make_unique<hid::EnvironmentalSettings>()} {}
    };
}