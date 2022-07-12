#pragma once

#include "scene_data.hpp"
#include "../renderer.hpp"
#include "../object.hpp"
#include "../components/camera.hpp"
#include "../wrapper/sdl_wrapper.hpp"

#include <cereal/cereal.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/archives/json.hpp>

#include <cereal/types/base_class.hpp>
#include <cereal/types/memory.hpp>

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

        std::string sceneName;

        Scene()
            : sceneData{std::make_shared<hid::SceneData>()},
              sceneName{"mainscene"}
        {
            auto mainCamera{createGameObject("Main Camera")};
            mainCamera->addComponent<Camera>(::displaySize.first, ::displaySize.second);
            mainCameraReference = &mainCamera->getComponent<Camera>();
            instantiate(std::move(mainCamera));
        }

        virtual ~Scene() = default;

        virtual void prepare() = 0;

        void start();
        void update();

        virtual void render(const hid::Renderer &renderer) = 0;

        void instantiate(std::unique_ptr<hid::Object> &&object);
        void instantiate(std::unique_ptr<hid::Object> &&object, const std::unique_ptr<hid::Object> &parent);

        std::unique_ptr<hid::Object> createGameObject(const std::string &name);
        std::unique_ptr<hid::Object> createUI(const std::string &name);
        // void saveSceneData() {}

        // void loadSceneData() {}

        template <class Archive>
        void serialize(Archive &archive)
        {
            archive(cereal::make_nvp("SceneData", *sceneData));
            archive.serializeDeferments();
        }
    };
} // namespace usr