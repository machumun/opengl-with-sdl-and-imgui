#include "vulkan_application.hpp"
#include "vulkan_asset_manager.hpp"

#include "../../../main/src/scene_main.hpp"

using hid::Application;
using hid::VulkanApplication;

VulkanApplication::VulkanApplication() : context{hid::VulkanContext()} {}

void VulkanApplication::update()
{
    Application::currentScene->update();
}

void VulkanApplication::render()
{
    if (context.renderBegin())
    {
        context.render();
        context.renderEnd();
    }
}

void VulkanApplication::start() {}

std::unique_ptr<hid::VulkanAssetManager> VulkanApplication::vulkanAssetManager = nullptr;

void VulkanApplication::setup()
{
    // SDL_GL_SetSwapInterval(0);
    vulkanAssetManager = std::make_unique<hid::VulkanAssetManager>();
    Application::assetManager = vulkanAssetManager.get();

    vulkanAssetManager->loadStandardStaticMeshes();

    ////
    currentScene = std::make_unique<hid::SceneMain>();
    context.loadAssetManifest(Application::currentScene->getAssetManifest());
}