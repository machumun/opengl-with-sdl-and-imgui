#include "engine.hpp"
#include "renderer.hpp"

#include "../application/opengl/opengl_application.hpp"

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

    switch (hid::RendererAPI::getAPI())
    {
    case RendererAPI::API::None:
        throw std::runtime_error(logTag + " No applications can run in the current environment");
        break;
    case RendererAPI::API::OpenGL:
        try
        {
            hid::log(logTag, "Creating OpenGL application ...");
            return std::make_unique<hid::OpenGLApplication>();
        }
        catch (const std::exception &error)
        {
            hid::log(logTag, "OpenGL application failed to initialize.", error);
        }
        break;
    }

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
