#include "engine.hpp"
#include "renderer.hpp"

#include "../application/opengl/opengl_application.hpp"

#include "../application/vulkan/vulkan_common.hpp"
#include "../application/vulkan/vulkan_application.hpp"

#include "log.hpp"
#include "wrapper/sdl_wrapper.hpp"
#include <stdexcept>
#include <string>

using hid::Engine;

Engine::Engine() : classLogTag{"hid::Engine::"}
{
}

std::unique_ptr<hid::Application> Engine::resolveApplication()
{
    static const std::string logTag{classLogTag + "resolveApplication"};

    if (hid::vulkan::isVulkanAvailable())
    {
        try
        {
            hid::log(logTag, "Creating Vulkan application...");
            // RendererAPI::api = RendererAPI::API::Vulkan;
            return std::make_unique<hid::VulkanApplication>();
        }
        catch (const std::exception &error)
        {
            hid::log(logTag, "Vulkan application failed to initialize.", error);
        }
    }
    try
    {
        hid::log(logTag, "Creating OpenGL application ...");
        return std::make_unique<hid::OpenGLApplication>();
    }
    catch (const std::exception &error)
    {
        hid::log(logTag, "OpenGL application failed to initialize.", error);
    }
    //     break;
    // }

    throw std::runtime_error(logTag + " No applications can run in the current environment");
}

void Engine::setup()
{
    static const std::string logTag{classLogTag + "setup"};
    hid::log(logTag, "Starting engine ...");
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    application = resolveApplication();
    application->setup();
}

void Engine::run()
{
    static const std::string logTag{classLogTag + "run"};
    hid::log(logTag, "SDL2 initialized successfully ...");
    application->startApplication();
}

Engine::~Engine()
{
    SDL_Quit();
}
