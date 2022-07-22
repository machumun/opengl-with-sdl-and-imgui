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

void VulkanApplication::setup()
{

    // SDL_GL_SetSwapInterval(0);
    assetManager = std::make_unique<hid::VulkanAssetManager>();
    assetManager->loadStandardStaticMeshes();

    ////
    currentScene = std::make_unique<hid::SceneMain>();
}