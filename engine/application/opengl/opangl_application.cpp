#include "opengl_application.hpp"

#include "../../core/wrapper/graphics_wrapper.hpp"
#include "../../core/log.hpp"

#include "../../core/wrapper/sdl_wrapper.hpp"
#include "../../core/sdl_window.hpp"

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

        // glEnable(GL_STENCIL_TEST);

        // glEnable(GL_MULTISAMPLE);

        glViewport(0, 0, viewportWidth, viewportHeight);

        return context;
    }

} // namespace

OpenGLApplication::OpenGLApplication() : Application(),
                                         window{hid::SDLWindow(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)},
                                         context{::createContext(window.getWindow())},
                                         renderer{std::make_unique<hid::OpenGLRenderer>()},
                                         imgui{std::make_unique<hid::OpenGLImGui>()}
{
}

void OpenGLApplication::update()
{
    currentScene->update();
    imgui->update(window.getWindow());
}

void OpenGLApplication::render()
{
    SDL_GL_MakeCurrent(window.getWindow(), context);

    renderer->render();
    imgui->render();

    SDL_GL_SwapWindow(window.getWindow());
}

void OpenGLApplication::setup()
{

    // SDL_GL_SetSwapInterval(0);
    assetManager = std::make_unique<hid::OpenGLAssetManager>();
    assetManager->loadStandardStaticMeshes();

    ////
    currentScene = std::make_unique<hid::SceneMain>();
    assetManager->loadAssetManifest(currentScene->getAssetManifest());
    ////

    layout = std::make_unique<hid::Layout>(currentScene->sceneData);
}

void OpenGLApplication::start()
{
    // use to load assets
    currentScene->prepare();

    // pointer delivery
    renderer->setup(currentScene->sceneData);
    std::function<void()> viewport = [&]() -> void
    { return layout->viewport(); };

    imgui->setup(window.getWindow(), context);
    imgui->setViewport(viewport);

    currentScene->start();
}

OpenGLApplication::~OpenGLApplication()
{
    imgui->cleanUp();
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window.getWindow());
}