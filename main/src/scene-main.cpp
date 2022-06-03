#include "scene-main.hpp"
#include "../../engine/core/animation-plane.hpp"
#include "../../engine/core/light-settings.hpp"
#include "../../engine/core/perspective-camera.hpp"
#include "../../engine/core/sdl-wrapper.hpp"
#include "../../engine/core/static-mesh-instance.hpp"
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

        assetManager.loadTextures({hid::assets::Texture::Empty});
        assetManager.loadTextures({hid::assets::Texture::Hamster});
        assetManager.loadTextures({hid::assets::Texture::Metal});
        assetManager.loadTextures({hid::assets::Texture::Magician});

        lightSettings = sharedUserData->lightSettings;

        hid::Material hamMaterial{hid::assets::Texture::Hamster,
                                  glm::vec3{1.0f, 1.0f, 1.0f}};

        hid::Material metalMaterial{hid::assets::Texture::Metal,
                                    glm::vec3{1.0f, 1.0f, 1.0f}};

        hid::Material charactorMaterial{hid::assets::Texture::Magician,
                                        glm::vec3{1.0f, 1.0f, 1.0f}};

        hid::Material pointLightMaterial{hid::assets::Texture::Empty,
                                         sharedUserData->lightSettings.pointLight.color};

        // 0
        staticMeshes.push_back(
            hid::StaticMeshInstance{
                hid::assets::StaticMesh::Crate,
                pointLightMaterial,
                sharedUserData->lightSettings.pointLight.position,
                glm::vec3{0.02f, 0.02f, 0.02f}});

        // 1
        staticMeshes.push_back(hid::StaticMeshInstance{
            hid::assets::StaticMesh::Hamster,
            hamMaterial});

        // 2
        staticMeshes.push_back(hid::StaticMeshInstance{
            hid::assets::StaticMesh::Hamster,
            metalMaterial,
            glm::vec3{-0.4f, 0.6f, 0.4f}, // Position
            glm::vec3{0.6f, 0.6f, 0.6f},  // Scale
            glm::vec3{0.0f, 0.4f, 0.9f},  // Rotation axis
            0.0f});

        // 3
        staticMeshes.push_back(hid::StaticMeshInstance{
            hid::assets::StaticMesh::Plane,
            metalMaterial,
            glm::vec3{0.4f, -0.5f, 0.4f}, // Position
            glm::vec3{1.6f, 1.6f, 1.6f},  // Scale
            glm::vec3{0.0f, 0.4f, 0.9f},  // Rotation axis
            0.0f});

        // 4
        staticMeshes.push_back(hid::StaticMeshInstance{
            hid::assets::StaticMesh::Plane,
            charactorMaterial,
            glm::vec3{1.0f, .5f, .0f}, // Position
            glm::vec3{.1f, .1f, .1f},  // Scale
            glm::vec3{1.0f, .0f, .0f}, // Rotation axis
            90.0f});
    }

    void update(const float& delta)
    {
        input(delta);
        camera.configure(player.getPosition(), player.getDirection());

        const glm::mat4 cameraMatrix{camera.getProjectionMatrix() * camera.getViewMatrix()};

        if (sharedUserData->isActive)
        {
            staticMeshes[1].rotateBy(delta * sharedUserData->rotateSpeed);
            staticMeshes[2].rotateBy(delta * sharedUserData->rotateSpeed);
        }

        // light instance
        staticMeshes[0].setPosition(sharedUserData->lightSettings.pointLight.position);
        staticMeshes[0].setBaseColor(sharedUserData->lightSettings.pointLight.color);

        // real time light move
        lightSettings = sharedUserData->lightSettings;

        for (auto& staticMesh : staticMeshes)
        {
            staticMesh.updateModelMatrix();
        }
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