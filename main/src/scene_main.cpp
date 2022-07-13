#include "scene_main.hpp"
#include "../../engine/application/application.hpp"
#include "../../engine/core/components/simple_components.hpp"

#include "../../engine/core/object.hpp"

#include "../../engine/core/wrapper/sdl_wrapper.hpp"

using hid::Application;
using hid::SceneMain;

#include <iostream>

CEREAL_REGISTER_TYPE(hid::SceneMain)
CEREAL_REGISTER_POLYMORPHIC_RELATION(hid::Scene, hid::SceneMain)

void SceneMain::render(const hid::Renderer& renderer)
{
    renderer.render();
}

// like awake ?

void SceneMain::prepare()
{
    Application::assetManager->loadStaticMeshes({{"hamster", "assets/models/hamster.obj"}});

    Application::assetManager->loadTextures({{"hamster", "assets/textures/hamster.png"},
                                             {"metal", "assets/textures/metal.png"},
                                             {"chara", "assets/textures/chara.png"},
                                             {"empty", "assets/textures/empty.png"},
                                             {"button_test", "assets/textures/button_art.png"}});

    // name {vert, frag}
    Application::assetManager->loadShader("lit", {"lit", "lit"});
    Application::assetManager->loadShader("animation", {"lit", "animation"});

    Application::assetManager->loadShader("ui", {"ui", "ui"});

    hid::Material metalMaterial{"lit", "metal"};
    hid::Material hamMaterial{"lit", "hamster"};

    hid::Material characterMaterial{"animation", "chara"};
    characterMaterial.alphaBlend = true;

    hid::Material uiMaterial{"ui", "button_test"};

    auto obj1{createGameObject("GameObject 1")};
    obj1->addComponent<MeshRenderer>("hamster", hamMaterial);
    instantiate(std::move(obj1));

    // plane group
    auto plane{createGameObject("Plane")};
    plane->addComponent<MeshRenderer>("plane", metalMaterial);
    plane->getComponent<Transform>().setPosition(glm::vec3{.0f, -1.f, .0f});

    auto plane_child{createGameObject("Plane Child")};
    plane_child->addComponent<MeshRenderer>("plane", metalMaterial);
    // plane->addChild(std::move(plane_child));
    instantiate(std::move(plane_child), plane);
    instantiate(std::move(plane));

    // for camera controller
    mainCameraReference->object->addComponent<PlayerController>(.0f);
    mainCameraReference->object->transform->position = glm::vec3{.0f, .0f, 2.f};

    auto pointLight{createGameObject("Point Light")};
    pointLight->addComponent<Light>(hid::LightType::Point,
                                    glm::vec3{216.f / 255.f, 218.f / 255.f, 192.f / 255.f},
                                    5.093f);
    pointLight->transform->position = glm::vec3{
        1.f,
        1.f,
        1.f};
    instantiate(std::move(pointLight));

    // character
    auto character{createGameObject("Charactor")};
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

    auto canvas{createUI("Canvas")};
    canvas->addComponent<Canvas>();

    auto button{createUI("Test SDL Button")};
    button->addComponent<UIButton>();
    button->getComponent<UIButton>().texture = "button_test";
    button->rectTransform->size = glm::vec2{160.f, 80.f};
    button->rectTransform->position = glm::vec2{-0.7f, 0.7f};

    instantiate(std::move(button), canvas);
    instantiate(std::move(canvas));
}
