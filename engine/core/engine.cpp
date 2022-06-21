#include "engine.hpp"

#include "log.hpp"
#include "sdl-wrapper.hpp"
#include <stdexcept>
#include <string>

using hid::Engine;

Engine::Engine() : classLogTag{"hid::Engine::"}
{
}

std::unique_ptr<hid::Application> Engine::resolveApplication()
{
    static const std::string logTag{classLogTag + "resolveApplication"};

    try
    {
        hid::log(logTag, "Creating OpenGL application ...");

        return std::make_unique<hid::OpenGLApplication>();
    }
    catch (const std::exception &error)
    {
        hid::log(logTag, "OpenGL application failed to initialize.", error);
    }
    throw std::runtime_error(logTag + " No applications can run in the current environment");
}

void Engine::init()
{
    static const std::string logTag{classLogTag + "init"};
    hid::log(logTag, "Starting engine ...");
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    application = resolveApplication();
    application->init();
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
