#include "scene-main.hpp"

#include "../../engine/core/components/mesh-renderer.hpp"
#include "../../engine/core/object.hpp"

using hid::SceneMain;

#include <iostream>

void SceneMain::update(const float& delta)
{
    // user data ->
    input(delta);
    camera.configure(player.getPosition(), player.getDirection());

    const glm::mat4 cameraMatrix{camera.getProjectionMatrix() * camera.getViewMatrix()};

    for (auto& object : sceneData->objects)
    {
        object->update();
    }
}

void SceneMain::input(const float& delta)
{
    if (keyboardState[SDL_SCANCODE_UP])
    {
        player.moveForward(delta);
    }

    if (keyboardState[SDL_SCANCODE_DOWN])
    {
        player.moveBackward(delta);
    }

    if (keyboardState[SDL_SCANCODE_A])
    {
        player.moveUp(delta);
    }

    if (keyboardState[SDL_SCANCODE_Z])
    {
        player.moveDown(delta);
    }

    if (keyboardState[SDL_SCANCODE_LEFT])
    {
        player.turnLeft(delta);
    }

    if (keyboardState[SDL_SCANCODE_RIGHT])
    {
        player.turnRight(delta);
    }
}

void SceneMain::render(hid::Renderer& renderer)
{
    renderer.render(hid::assets::Pipeline::LitPass, sceneData, camera);
}

void SceneMain::prepare(hid::AssetManager& assetManager)
{

    sceneData->rotateSpeed = 50.0f;

    assetManager.loadPipelines({hid::assets::Pipeline::LitPass});

    assetManager.loadStaticMeshes({{"plane", "assets/models/plane.obj"},
                                   {"hamster", "assets/models/hamster.obj"},
                                   {"crate", "assets/models/crate.obj"}});

    // to memory
    assetManager.loadTextures({{"hamster", "assets/textures/hamster.png"},
                               {"metal", "assets/textures/metal.png"},
                               {"chara", "assets/textures/chara.png"},
                               {"empty", "assets/textures/empty.png"}});

    assetManager.loadGLTFModels({hid::assets::GLTF::TestBox});

    // std::shared_ptr<hid::Material> hamMaterial =
    //     std::make_shared<hid::Material>("hamster",
    //                                     glm::vec3{1.0f, 1.0f, 1.0f});

    hid::Material metalMaterial{"metal",
                                glm::vec3{1.0f, 1.0f, 1.0f}};

    hid::Material hamMaterial{"hamster",
                              glm::vec3{1.0f, 1.0f, 1.0f}};

    hid::Material characterMaterial{"chara",
                                    glm::vec3{1.0f, 1.0f, 1.0f}};

    hid::Material pointLightMaterial{"empty",
                                     sceneData->lightSettings.pointLight.color};

    const std::shared_ptr<hid::Object> obj1 = std::make_shared<hid::Object>();

    // arg1: mesh string
    // arg2: material
    obj1->addComponent<MeshRenderer>("hamster", hamMaterial);
    sceneData->objects.emplace_back(obj1);
}