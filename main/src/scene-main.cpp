#include "scene-main.hpp"
#include "../../engine/core/light-settings.hpp"
#include "../../engine/core/perspective-camera.hpp"
#include "../../engine/core/static-mesh-instance.hpp"

#include "../../engine/core/sdl-wrapper.hpp"

#include "player.hpp"

using usr::SceneMain;
// using namespace hid;

#include <iostream>

namespace
{

    hid::PerspectiveCamera createCamera(const float& width, const float& height)
    {
        return hid::PerspectiveCamera(width, height);
    }
} // namespace

struct SceneMain::Internal
{
    hid::PerspectiveCamera camera;
    std::vector<hid::StaticMeshInstance> staticMeshesUnlit;
    std::vector<hid::StaticMeshInstance> staticMeshesLit;
    std::vector<hid::StaticMeshInstance> lightInstance;

    std::shared_ptr<hid::Dat> sharedUserData;
    // hid::Dat* sharedUserData;
    // std::shared_ptr<hid::Dat> sharedUserData;

    hid::LightSettings lightSettings;

    hid::Player player;

    const uint8_t* keyboardState;

    Internal(const float& screenWidth, const float& screenHeight)
        : camera(::createCamera(screenWidth, screenHeight)),
          lightSettings(hid::Light(hid::LightType::Point), hid::Light(hid::LightType::Ambient)),
          player(hid::Player(glm::vec3{0.0f, 0.0f, 2.0f}, 0.0f)),
          keyboardState(SDL_GetKeyboardState(nullptr)),
          sharedUserData(nullptr)
    {
    }

    void prepare(hid::AssetManager& assetManager, const std::shared_ptr<hid::Dat> userData)
    {

        userData->rotateSpeed = 50.0f;
        sharedUserData = userData;

        // assetManager.loadPipelines({hid::assets::Pipeline::DefaultPass});
        assetManager.loadPipelines({hid::assets::Pipeline::LitPass});
        // assetManager.loadPipelines({hid::assets::Pipeline::BlurPass});

        assetManager.loadStaticMeshes({hid::assets::StaticMesh::Hamster});
        assetManager.loadStaticMeshes({hid::assets::StaticMesh::Plane});
        assetManager.loadStaticMeshes({hid::assets::StaticMesh::Crate});

        assetManager.loadTextures({hid::assets::Texture::Hamster});
        assetManager.loadTextures({hid::assets::Texture::Metal});

        // staticMeshesUnlit.push_back(hid::StaticMeshInstance{
        //     hid::assets::StaticMesh::Hamster,
        //     hid::assets::Texture::Hamster});

        staticMeshesLit.push_back(hid::StaticMeshInstance{
            hid::assets::StaticMesh::Hamster,
            hid::assets::Texture::Hamster});

        staticMeshesLit.push_back(hid::StaticMeshInstance{
            hid::assets::StaticMesh::Hamster,
            hid::assets::Texture::Metal,
            glm::vec3{0.4f, 0.6f, 0.4f}, // Position
            glm::vec3{0.6f, 0.6f, 0.6f}, // Scale
            glm::vec3{0.0f, 0.4f, 0.9f}, // Rotation axis
            0.0f});

        // staticMeshesLit.push_back(hid::StaticMeshInstance{
        //     hid::assets::StaticMesh::Plane,
        //     hid::assets::Texture::Hamster,
        //     glm::vec3{0.0f, -1.6f, 0.0f},
        //     glm::vec3{10.6f, 10.6f, 10.6f}});

        staticMeshesLit.push_back(
            hid::StaticMeshInstance{
                hid::assets::StaticMesh::Crate,
                hid::assets::Texture::Metal,
                sharedUserData->pointLightPosition,
                glm::vec3{0.2f, 0.2f, 0.2f}});

        lightSettings.pointLight.setPosition(sharedUserData->pointLightPosition);
        lightSettings.pointLight.setColor(sharedUserData->pointLightColor);
        lightSettings.pointLight.setStrength(sharedUserData->pointLightStrength);
        lightSettings.ambientLight.setColor(sharedUserData->ambientLightColor);
        lightSettings.ambientLight.setStrength(sharedUserData->ambientLightStrength);

        // staticMeshes.push_back(hid::StaticMeshInstance{
        //     hid::assets::StaticMesh::Monkey,
        //     hid::assets::Texture::Cube,
        //     glm::vec3{0.4f, 0.6f, 0.0f}, // Position
        //     glm::vec3{0.6f, 0.6f, 0.6f}, // Scale
        //     glm::vec3{0.0f, 0.4f, 0.9f}, // Rotation axis
        //     0.0f});
    }

    void update(const float& delta)
    {
        input(delta);
        camera.configure(player.getPosition(), player.getDirection());

        const glm::mat4 cameraMatrix{camera.getProjectionMatrix() * camera.getViewMatrix()};

        if (sharedUserData->isActive)
        {
            staticMeshesLit.at(0).rotateBy(delta * sharedUserData->rotateSpeed);
            staticMeshesLit.at(1).rotateBy(delta * sharedUserData->rotateSpeed);
        }

        staticMeshesLit.at(0).updateModelMatrix();
        staticMeshesLit.at(1).updateModelMatrix();

        staticMeshesLit.at(2).setPosition(sharedUserData->pointLightPosition);
        staticMeshesLit.at(2).updateModelMatrix();

        // for (auto& staticMesh : staticMeshesUnlit)
        // {
        //     if (sharedUserData->isActive)
        //     {
        //         staticMesh.rotateBy(delta * sharedUserData->rotateSpeed);
        //     }

        //     staticMesh.update(cameraMatrix);
        // }
        // for (auto& staticMesh : staticMeshesLit)
        // {
        //     if (sharedUserData->isActive)
        //     {
        //         staticMesh.rotateBy(delta * sharedUserData->rotateSpeed);
        //     }

        //     staticMesh.update(cameraMatrix);
        // }

        // real time light move
        lightSettings.pointLight.setPosition(sharedUserData->pointLightPosition);
        lightSettings.pointLight.setColor(sharedUserData->pointLightColor);
        lightSettings.pointLight.setStrength(sharedUserData->pointLightStrength);
        lightSettings.ambientLight.setColor(sharedUserData->ambientLightColor);
        lightSettings.ambientLight.setStrength(sharedUserData->ambientLightStrength);
    }

    void render(hid::Renderer& renderer)
    {
        renderer.render(hid::assets::Pipeline::LitPass, staticMeshesLit, camera, lightSettings);
    }

    void input(const float& delta)
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
};

SceneMain::SceneMain(const float& screenWidth, const float& screenHeight)
    : internal(hid::make_internal_ptr<Internal>(screenWidth, screenHeight)) {}

void SceneMain::prepare(hid::AssetManager& assetManager,
                        const std::shared_ptr<hid::Dat> userData)
{
    internal->prepare(assetManager, userData);
}

void SceneMain::update(const float& delta)
{
    internal->update(delta);
}

void SceneMain::render(hid::Renderer& renderer)
{
    internal->render(renderer);
}