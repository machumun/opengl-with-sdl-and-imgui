#pragma once

#include "environmental_settings.hpp"
#include "../asset_manager.hpp"

#include "../wrapper/glm_wrapper.hpp"

#include "../object.hpp"

#include <unordered_map>

#include <cereal/cereal.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/archives/json.hpp>

namespace hid
{
    struct SceneData
    {
        std::vector<std::unique_ptr<hid::Object>> objects;
        // std::unordered_map<uint32_t, hid::Object *> objectsMap;
        std::unique_ptr<hid::EnvironmentalSettings> environmentalSettings;
        SceneData()
            : environmentalSettings{std::make_unique<hid::EnvironmentalSettings>()} {}

        template <class Archive>
        void serialize(Archive &archive)
        {
            for (auto &object : objects)
            {
                archive(cereal::make_nvp("object", *object));
            }

            archive(cereal::make_nvp("environmentalSettings", *environmentalSettings));
        }
    };
}