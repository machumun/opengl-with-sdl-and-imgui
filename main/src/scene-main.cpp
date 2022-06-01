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
    std::vector<hid::StaticMeshInstance> staticMeshes;
    std::vector<hid::StaticMeshInstance> lightInstance;

    std::shared_ptr<hid::Dat> sharedUserData;

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

        assetManager.loadPipelines({hid::assets::Pipeline::LitPass});

        assetManager.loadStaticMeshes({hid::assets::StaticMesh::Hamster});
        assetManager.loadStaticMeshes({hid::assets::StaticMesh::Plane});
        assetManager.loadStaticMeshes({hid::assets::StaticMesh::Crate});

        assetManager.loadTextures({hid::assets::Texture::Hamster});
        assetManager.loadTextures({hid::assets::Texture::Metal});

        staticMeshes.push_back(hid::StaticMeshInstance{
            hid::assets::StaticMesh::Hamster,
            hid::assets::Texture::Hamster});

        staticMeshes.push_back(hid::StaticMeshInstance{
            hid::assets::StaticMesh::Hamster,
            hid::assets::Texture::Metal,
            glm::vec3{0.4f, 0.6f, 0.4f}, // Position
            glm::vec3{0.6f, 0.6f, 0.6f}, // Scale
            glm::vec3{0.0f, 0.4f, 0.9f}, // Rotation axis
            0.0f});

        staticMeshes.push_back(
            hid::StaticMeshInstance{
                hid::assets::StaticMesh::Crate,
                hid::assets::Texture::Metal,
                sharedUserData->pointLightPosition,
                glm::vec3{0.2f, 0.2f, 0.2f}});

        staticMeshes.push_back(hid::StaticMeshInstance{
            hid::assets::StaticMesh::Plane,
            hid::assets::Texture::Metal,
            glm::vec3{0.4f, -0.5f, 0.4f}, // Position
            glm::vec3{1.6f, 1.6f, 1.6f},  // Scale
            glm::vec3{0.0f, 0.4f, 0.9f},  // Rotation axis
            0.0f});

        lightSettings.pointLight.setPosition(sharedUserData->pointLightPosition);
        lightSettings.pointLight.setColor(sharedUserData->pointLightColor);
        lightSettings.pointLight.setIntensity(sharedUserData->pointLightIntensity);
        lightSettings.ambientLight.setColor(sharedUserData->ambientLightColor);
        lightSettings.ambientLight.setIntensity(sharedUserData->ambientLightIntensity);

        lightSettings.bloomIntensity = sharedUserData->bloomIntensity;
        lightSettings.bloom = sharedUserData->bloom;
    }

    void update(const float& delta)
    {
        input(delta);
        camera.configure(player.getPosition(), player.getDirection());

        const glm::mat4 cameraMatrix{camera.getProjectionMatrix() * camera.getViewMatrix()};

        if (sharedUserData->isActive)
        {
            staticMeshes.at(0).rotateBy(delta * sharedUserData->rotateSpeed);
            staticMeshes.at(1).rotateBy(delta * sharedUserData->rotateSpeed);
        }

        staticMeshes.at(0).updateModelMatrix();
        staticMeshes.at(1).updateModelMatrix();

        staticMeshes.at(2).setPosition(sharedUserData->pointLightPosition);
        staticMeshes.at(2).updateModelMatrix();

        staticMeshes.at(3).updateModelMatrix();

        // real time light move
        lightSettings.pointLight.setPosition(sharedUserData->pointLightPosition);
        lightSettings.pointLight.setColor(sharedUserData->pointLightColor);
        lightSettings.pointLight.setIntensity(sharedUserData->pointLightIntensity);
        lightSettings.ambientLight.setColor(sharedUserData->ambientLightColor);
        lightSettings.ambientLight.setIntensity(sharedUserData->ambientLightIntensity);
        lightSettings.bloomIntensity = sharedUserData->bloomIntensity;
        lightSettings.bloom = sharedUserData->bloom;
    }

    void render(hid::Renderer& renderer)
    {
        renderer.render(hid::assets::Pipeline::LitPass, staticMeshes, camera, lightSettings);
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