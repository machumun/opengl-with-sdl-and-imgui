#pragma once

#include "scene/scene_data.hpp"

#include <vector>

namespace hid
{
    struct RendererAPI
    {
        enum class API
        {
            None = 0,
            OpenGL = 1,
            Vulkan = 2
        };

        inline static API getAPI() { return api; }

    private:
        static API api;
    };
    struct Renderer
    {
        virtual const void render() const = 0;
        virtual void setup(std::shared_ptr<hid::SceneData> sceneData) = 0;
    };
}