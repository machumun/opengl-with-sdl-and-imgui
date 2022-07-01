#pragma once

#include "scene_data.hpp"

#include "../renderer.hpp"

#include "../object.hpp"

#include "../components/camera.hpp"

#include "../wrapper/sdl_wrapper.hpp"

namespace
{
    static std::pair<uint32_t, uint32_t> displaySize{hid::sdl::getDisplaySize()};

} // namespace

namespace hid
{

    struct Scene
    {

        std::shared_ptr<hid::SceneData> sceneData;
        hid::Camera *mainCameraReference;

        Scene() : sceneData{std::make_shared<hid::SceneData>()}
        {
            auto mainCamera{std::make_unique<hid::Object>("Main Camera")};
            mainCamera->addComponent<Camera>(::displaySize.first, ::displaySize.second);
            mainCameraReference = &mainCamera->getComponent<Camera>();
            instantiate(std::move(mainCamera));
        }

        virtual ~Scene() = default;

        virtual void prepare() = 0;

        virtual void start()
        {
            for (auto &object : sceneData->objects)
            {
                object->start();
            }
        };

        virtual void update(const float &delta) = 0;

        virtual void render(const hid::Renderer &renderer) = 0;

        void instantiate(std::unique_ptr<hid::Object> &&object);
    };
} // namespace usr