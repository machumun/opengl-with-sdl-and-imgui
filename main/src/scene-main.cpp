#include "scene-main.hpp"

#include "../../core/material.hpp"
#include "../../core/object.hpp"

using hid::SceneMain;
// using namespace hid;

#include <iostream>

void SceneMain::update(const float& delta)
{

    // user data ->
    input(delta);
    camera.configure(player.getPosition(), player.getDirection());

    const glm::mat4 cameraMatrix{camera.getProjectionMatrix() * camera.getViewMatrix()};

    // for (auto& staticMesh : sceneData->staticMeshInstances)
    // {
    //     staticMesh->updateModelMatrix();
    // }
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

    assetManager.loadStaticMeshes({hid::assets::StaticMesh::Plane,
                                   hid::assets::StaticMesh::Hamster,
                                   hid::assets::StaticMesh::Crate});

    assetManager.loadTextures({hid::assets::Texture::Empty,
                               hid::assets::Texture::Hamster,
                               hid::assets::Texture::Metal,
                               hid::assets::Texture::Frog});

    assetManager.loadGLTFModels({hid::assets::GLTF::TestBox});

    hid::Material hamMaterial{hid::assets::Texture::Hamster,
                              glm::vec3{1.0f, 1.0f, 1.0f}};

    hid::Material metalMaterial{hid::assets::Texture::Metal,
                                glm::vec3{1.0f, 1.0f, 1.0f}};

    hid::Material characterMaterial{hid::assets::Texture::Frog,
                                    glm::vec3{1.0f, 1.0f, 1.0f}};

    hid::Material pointLightMaterial{hid::assets::Texture::Empty,
                                     sceneData->lightSettings.pointLight.color};

    std::shared_ptr<hid::Object> obj1 = std::make_shared<hid::Object>();
}