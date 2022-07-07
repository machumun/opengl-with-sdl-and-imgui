#include "opengl_application.hpp"

#include "../../core/wrapper/graphics_wrapper.hpp"
#include "../../core/log.hpp"
#include "../../core/wrapper/sdl_wrapper.hpp"
#include "../../core/scene/scene_data.hpp"

#include "../../core/layout/layout.hpp"

#include <iostream>

using hid::Application;
using hid::OpenGLApplication;

namespace
{

    SDL_GLContext createContext(SDL_Window *window)
    {
        static const std::string logTag{"hid::OpenGLApplication::createContext"};

        SDL_GLContext context{SDL_GL_CreateContext(window)};
#ifdef WIN32
        glewInit();
#endif

        int viewportWidth;
        int viewportHeight;

        SDL_GL_GetDrawableSize(window, &viewportWidth, &viewportHeight);
        hid::log(logTag, "Created OpenGL context with viewport size: " + std::to_string(viewportWidth) + " x " + std::to_string(viewportHeight));

        glClearDepthf(1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glFrontFace(GL_CW);

        // glEnable(GL_MULTISAMPLE);

        glViewport(0, 0, viewportWidth, viewportHeight);

        return context;
    }

    int32_t resizingEventWatcher(void *data, SDL_Event *event)
    {
        static const std::string logTag{"hid::OpenGLApplication::resizingEventWatcher"};

        if (event->type == SDL_WINDOWEVENT &&
            event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
        {
            SDL_Window *win = SDL_GetWindowFromID(event->window.windowID);
            if (win == (SDL_Window *)data)
            {
                hid::log(logTag, "Window size was Changed.");
            }
        }

        return 0;
    }
} // namespace

OpenGLApplication::OpenGLApplication() : Application(),
                                         window{hid::sdl::createWindow(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)},
                                         context{::createContext(window)},
                                         renderer{std::make_unique<hid::OpenGLRenderer>()},
                                         scene{std::make_unique<hid::SceneMain>()},
                                         layout{std::make_unique<hid::Layout>(scene->sceneData)},
                                         imgui{std::make_unique<hid::OpenGLImGui>()}
{
}

void OpenGLApplication::update()
{
    scene->update();
    imgui->update(window);
}

void OpenGLApplication::render()
{
    SDL_GL_MakeCurrent(window, context);

    renderer->render();
    imgui->render();

    SDL_GL_SwapWindow(window);
}

void OpenGLApplication::setup()
{
    // SDL_AddEventWatch(::resizingEventWatcher, window);
    // SDL_GL_SetSwapInterval(0);
    Application::assetManager = std::make_unique<hid::OpenGLAssetManager>();
    Application::assetManager->loadStandardStaticMeshes();
}

void OpenGLApplication::start()
{
    // use to load assets
    scene->prepare();

    // pointer delivery
    renderer->setup(scene->sceneData);
    std::function<void()> viewport = [&]() -> void
    { return layout->viewport(); };

    imgui->setup(window, context);
    imgui->setViewport(viewport);

    scene->start();
}

OpenGLApplication::~OpenGLApplication()
{
    imgui->cleanUp();
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
}