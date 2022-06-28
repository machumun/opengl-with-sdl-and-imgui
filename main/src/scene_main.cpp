#include "scene_main.hpp"

#include "../../engine/core/components/simple_components.hpp"

#include "../../engine/core/object.hpp"

#include "../../engine/core/wrapper/sdl_wrapper.hpp"

using hid::SceneMain;

#include <iostream>

void SceneMain::update(const float& delta)
{
    playerController->input(delta);

    for (auto& object : sceneData->objects)
    {
        object->update();
    }
}

void SceneMain::render(hid::Renderer& renderer)
{
    renderer.render(hid::assets::Pipeline::LitPass);
}

// like awake ?
void SceneMain::prepare(hid::AssetManager& assetManager)
{

    assetManager.loadPipelines({hid::assets::Pipeline::LitPass});

    assetManager.loadStaticMeshes({{"plane", "assets/models/plane.obj"},
                                   {"hamster", "assets/models/hamster.obj"},
                                   {"crate", "assets/models/crate.obj"}});

    assetManager.loadTextures({{"hamster", "assets/textures/hamster.png"},
                               {"metal", "assets/textures/metal.png"},
                               {"chara", "assets/textures/chara.png"},
                               {"empty", "assets/textures/empty.png"}});

    assetManager.loadGLTFModels({hid::assets::GLTF::TestBox});

    // planning load shaders

    hid::Material metalMaterial{"metal",
                                glm::vec3{1.0f, 1.0f, 1.0f}};

    hid::Material hamMaterial{"hamster",
                              glm::vec3{1.0f, 1.0f, 1.0f}};

    hid::Material characterMaterial{"chara",
                                    glm::vec3{1.0f, 1.0f, 1.0f}};

    auto obj1{std::make_shared<hid::Object>("GameObject 1")};
    obj1->addComponent<MeshRenderer>("hamster", hamMaterial);
    instantiate(obj1);

    auto plane{std::make_shared<hid::Object>("Plane")};
    plane->addComponent<MeshRenderer>("plane", metalMaterial);
    plane->getComponent<Transform>().setPosition(glm::vec3{.0f, -1.f, .0f});
    instantiate(plane);

    mainCamera->addComponent<PlayerController>(.0f);
    mainCamera->getComponent<Transform>().position = glm::vec3{.0f, .0f, 2.f};
    playerController = &mainCamera->getComponent<PlayerController>();

    auto pointLight{std::make_shared<hid::Object>("Point Light")};
    pointLight->addComponent<Light>(hid::LightType::Point,
                                    glm::vec3{216.f / 255.f, 218.f / 255.f, 192.f / 255.f},
                                    5.093f);
    pointLight->transform->position = glm::vec3{
        1.f,
        1.f,
        1.f,
    };
    instantiate(pointLight);

    // character
    auto character{std::make_shared<hid::Object>("Charactor")};
    std::vector<uint32_t> animationFrame{0, 1, 2, 1};
    character->addComponent<AnimationPlane>(
        characterMaterial,
        animationFrame,
        10,
        6,
        4);
    character->transform->rotationAxis = glm::vec3{1.f, .0f, .0f};
    character->transform->rotationDegrees = 90.f;
    character->transform->scale = glm::vec3{
        .2f,
        .2f,
        .2f};
    character->transform->position.x = 1.f;
    instantiate(character);
}
