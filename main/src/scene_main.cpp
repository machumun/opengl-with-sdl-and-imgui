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
void SceneMain::prepare()
{
    sceneData->assetManager->loadStaticMeshes({{"plane", "assets/models/plane.obj"},
                                               {"hamster", "assets/models/hamster.obj"},
                                               {"crate", "assets/models/crate.obj"}});

    sceneData->assetManager->loadTextures({{"hamster", "assets/textures/hamster.png"},
                                           {"metal", "assets/textures/metal.png"},
                                           {"chara", "assets/textures/chara.png"},
                                           {"empty", "assets/textures/empty.png"}});

    sceneData->assetManager->loadGLTFModels({hid::assets::GLTF::TestBox});

    // name {vert, frag}
    sceneData->assetManager->loadShader("lit", {"lit", "lit"});

    hid::Material metalMaterial{
        "lit",
        "metal",
        glm::vec3{1.0f, 1.0f, 1.0f}};

    hid::Material hamMaterial{
        "lit",
        "hamster",
        glm::vec3{1.0f, 1.0f, 1.0f}};

    hid::Material characterMaterial{
        "animation",
        "chara",
        glm::vec3{1.0f, 1.0f, 1.0f}};

    auto obj1{std::make_unique<hid::Object>("GameObject 1")};
    obj1->addComponent<MeshRenderer>("hamster", hamMaterial);
    instantiate(std::move(obj1));

    auto plane{std::make_unique<hid::Object>("Plane")};
    plane->addComponent<MeshRenderer>("plane", metalMaterial);
    plane->getComponent<Transform>().setPosition(glm::vec3{.0f, -1.f, .0f});
    instantiate(std::move(plane));

    sceneData->objects[0]->addComponent<PlayerController>(.0f);
    sceneData->objects[0]->getComponent<Transform>().position = glm::vec3{.0f, .0f, 2.f};
    playerController = &sceneData->objects[0]->getComponent<PlayerController>();

    auto pointLight{std::make_unique<hid::Object>("Point Light")};
    pointLight->addComponent<Light>(hid::LightType::Point,
                                    glm::vec3{216.f / 255.f, 218.f / 255.f, 192.f / 255.f},
                                    5.093f);
    pointLight->transform->position = glm::vec3{
        1.f,
        1.f,
        1.f};
    instantiate(std::move(pointLight));

    // character
    auto character{std::make_unique<hid::Object>("Charactor")};
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
    instantiate(std::move(character));
}
