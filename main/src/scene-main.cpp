#include "scene-main.hpp"

using hid::SceneMain;
// using namespace hid;

#include <iostream>

void SceneMain::update(const float& delta)
{

    // user data ->
    input(delta);
    camera.configure(player.getPosition(), player.getDirection());

    const glm::mat4 cameraMatrix{camera.getProjectionMatrix() * camera.getViewMatrix()};

    // if (sceneData->isActive)
    // {
    //     staticMeshes[1].rotateBy(delta * sceneData->rotateSpeed);
    //     staticMeshes[2].rotateBy(delta * sceneData->rotateSpeed);
    // }

    // light instance
    // staticMeshes[0].setPosition(sceneData->lightSettings.pointLight.position);
    // staticMeshes[0].setBaseColor(sceneData->lightSettings.pointLight.color);

    // real time light move
    // lightSettings = sceneData->lightSettings;

    for (auto& staticMesh : sceneData->staticMeshInstances)
    {
        staticMesh->updateModelMatrix();
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

    // 0
    sceneData->staticMeshInstances.emplace_back(
        std::make_shared<hid::StaticMeshInstance>(
            hid::StaticMeshInstance{
                hid::assets::StaticMesh::Plane,
                metalMaterial,
                glm::vec3{0.4f, -0.5f, 0.4f}, // Position
                glm::vec3{1.6f, 1.6f, 1.6f},  // Scale
                glm::vec3{0.0f, 0.4f, 0.9f},  // Rotation axis
                0.0f}));

    // 1
    sceneData->staticMeshInstances.emplace_back(
        std::make_shared<hid::StaticMeshInstance>(
            hid::StaticMeshInstance{
                hid::assets::StaticMesh::Hamster,
                hamMaterial}));

    // とりあえずgltfをstringから読み込む
    sceneData->gltfs.emplace_back(hid::assets::GLTF::TestBox);

    // staticMeshes.push_back(
    //     hid::StaticMeshInstance{
    //         hid::assets::StaticMesh::Crate,
    //         pointLightMaterial,
    //         sceneData->lightSettings.pointLight.position,
    //         glm::vec3{0.02f, 0.02f, 0.02f}});

    // // 1
    // staticMeshes.push_back(hid::StaticMeshInstance{
    //     hid::assets::StaticMesh::Hamster,
    //     hamMaterial});

    // // 2
    // staticMeshes.push_back(hid::StaticMeshInstance{
    //     hid::assets::StaticMesh::Hamster,
    //     metalMaterial,
    //     glm::vec3{-0.4f, 0.6f, 0.4f}, // Position
    //     glm::vec3{0.6f, 0.6f, 0.6f},  // Scale
    //     glm::vec3{0.0f, 0.4f, 0.9f},  // Rotation axis
    //     0.0f});

    // // 3
    // staticMeshes.push_back(hid::StaticMeshInstance{
    //     hid::assets::StaticMesh::Plane,
    //     metalMaterial,
    //     glm::vec3{0.4f, -0.5f, 0.4f}, // Position
    //     glm::vec3{1.6f, 1.6f, 1.6f},  // Scale
    //     glm::vec3{0.0f, 0.4f, 0.9f},  // Rotation axis
    //     0.0f});

    // // 4
    // staticMeshes.push_back(hid::StaticMeshInstance{
    //     hid::assets::StaticMesh::Plane,
    //     characterMaterial,
    //     glm::vec3{1.0f, .0f, .0f}, // Position
    //     glm::vec3{.1f, .1f, .1f},  // Scale
    //     glm::vec3{1.0f, .0f, .0f}, // Rotation axis
    //     90.0f});

    // a0
    // animationPlanes.push_back(
    //     hid::AnimationPlane{
    //         characterMaterial,
    //         0,
    //         glm::vec3{1.0f, .5f, .0f}, // Position
    //         glm::vec3{.1f, .1f, .1f},  // Scale
    //         glm::vec3{1.0f, .0f, .0f}, // Rotation axis
    //         90.0f});
}