#include "scene_main.hpp"

#include "../../engine/core/components/mesh_renderer.hpp"
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

    assetManager.loadPipelines({hid::assets::Pipeline::LitPass});

    assetManager.loadStaticMeshes({{"plane", "assets/models/plane.obj"},
                                   {"hamster", "assets/models/hamster.obj"},
                                   {"crate", "assets/models/crate.obj"}});

    assetManager.loadTextures({{"hamster", "assets/textures/hamster.png"},
                               {"metal", "assets/textures/metal.png"},
                               {"chara", "assets/textures/chara.png"},
                               {"empty", "assets/textures/empty.png"}});

    assetManager.loadGLTFModels({hid::assets::GLTF::TestBox});

    hid::Material metalMaterial{"metal",
                                glm::vec3{1.0f, 1.0f, 1.0f}};

    hid::Material hamMaterial{"hamster",
                              glm::vec3{1.0f, 1.0f, 1.0f}};

    hid::Material characterMaterial{"chara",
                                    glm::vec3{1.0f, 1.0f, 1.0f}};

    hid::Material pointLightMaterial{"empty",
                                     sceneData->lightSettings.pointLight.color};

    auto obj1{std::make_shared<hid::Object>("GameObject 1")};
    obj1->addComponent<MeshRenderer>("hamster", hamMaterial);
    instantiate(obj1);

    auto plane{std::make_shared<hid::Object>("Plane")};
    plane->addComponent<MeshRenderer>("plane", metalMaterial);
    plane->getComponent<Transform>().setPosition(glm::vec3{.0f, -1.f, .0f});
    instantiate(plane);
}