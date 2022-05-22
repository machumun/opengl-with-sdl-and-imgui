#include "engine.hpp"
#include "../application/application.hpp"
#include "../application/opengl/opengl-application.hpp"
#include "log.hpp"
#include "sdl-wrapper.hpp"
#include <stdexcept>
#include <string>

using hid::Engine;

struct Engine::Internal
{
    const std::string classLogTag;

    std::unique_ptr<hid::Application> application;

    Internal() : classLogTag("hid::Engine::")
    {
    }

    std::unique_ptr<hid::Application> resolveApplication()
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

    void init()
    {
        static const std::string logTag{classLogTag + "init"};
        hid::log(logTag, "Starting engine ...");
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
        application = resolveApplication();
        application->init();
    }

    void run()
    {

        static const std::string logTag{classLogTag + "run"};
        hid::log(logTag, "SDL2 initialized successfully ...");
        application->startApplication();
    }

    void setUserImGui(std::function<void()> fp)
    {
        static const std::string logTag{classLogTag + "setUserImGui"};
        hid::log(logTag, "Setup user ImGui ...");
        // application->setUserImGui(fp);
    }

    ~Internal()
    {
        SDL_Quit();
    }
};

Engine::Engine() : internal(hid::make_internal_ptr<Internal>()) {}

void Engine::init()
{
    internal->init();
}

void Engine::run()
{
    internal->run();
}