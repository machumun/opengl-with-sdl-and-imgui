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

        hid::Camera *editorCameraRefernce;

        Scene() : sceneData{std::make_shared<hid::SceneData>()}
        {
            auto mainCamera{std::make_unique<hid::Object>("Main Camera")};
            mainCamera->addComponent<Camera>(::displaySize.first, ::displaySize.second);
            mainCameraReference = &mainCamera->getComponent<Camera>();
            instantiate(std::move(mainCamera));

            auto editorCamera{std::make_unique<hid::Object>("Editor Camera")};
            editorCamera->addComponent<Camera>(::displaySize.first, ::displaySize.second);
            editorCameraRefernce = &editorCamera->getComponent<Camera>();
            instantiate(std::move(editorCamera));
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

        // runtime
        virtual void update(const float &delta) = 0;

        void updateEditor(const float &delta);

        virtual void render(const hid::Renderer &renderer) = 0;

        void instantiate(std::unique_ptr<hid::Object> &&object);
        void instantiate(std::unique_ptr<hid::Object> &&object, const std::unique_ptr<hid::Object> &parent);

        // void saveSceneData() {}

        // void loadSceneData() {}
    };
} // namespace usr