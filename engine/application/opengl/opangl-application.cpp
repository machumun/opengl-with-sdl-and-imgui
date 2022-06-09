#include "opengl-application.hpp"
#include "opengl-imgui.hpp"
#include "../../core/graphics-wrapper.hpp"
#include "../../core/log.hpp"
#include "../../core/sdl-wrapper.hpp"
#include "../../../main/src/scene-main.hpp"
#include "opengl-asset-manager.hpp"
#include "opengl-renderer.hpp"

#include <iostream>

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

    std::shared_ptr<hid::OpenGLAssetManager> createAssetManager()
    {
        return std::make_shared<hid::OpenGLAssetManager>(hid::OpenGLAssetManager());
    }

    hid::OpenGLRenderer createRenderer(std::shared_ptr<hid::OpenGLAssetManager> assetManager)
    {
        return hid::OpenGLRenderer(assetManager);
    }

    std::unique_ptr<hid::Scene> createMainScene(hid::AssetManager &assetManager, std::shared_ptr<hid::Dat> &userData)
    {

        std::unique_ptr<hid::Scene> scene{std::make_unique<hid::SceneMain>(userData)};
        scene->prepare(assetManager);
        return scene;
    }

    std::shared_ptr<hid::Dat> createUserData()
    {
        return std::make_shared<hid::Dat>(hid::Dat());
    }

    int32_t resizingEventWatcher(void *data, SDL_Event *event)
    {
        static const std::string logTag{"hid::OpenGLApplication::resizingEventWatcher"};

        // if (event->type == SDL_WINDOWEVENT &&
        //     event->window.event == SDL_WINDOWEVENT_RESIZED)
        // {
        //     SDL_Window *win = SDL_GetWindowFromID(event->window.windowID);
        //     if (win == (SDL_Window *)data)
        //     {
        //         hid::log(logTag, "Window is resizing");
        //     }
        // }

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

struct hid::OpenGLApplication::Internal
{
    SDL_Window *window;
    SDL_GLContext context;

    std::unique_ptr<hid::OpenGLImGui> imgui;

    const std::shared_ptr<hid::OpenGLAssetManager> assetManager;

    // user data
    std::shared_ptr<hid::Dat> data;

    hid::OpenGLRenderer renderer;

    std::unique_ptr<hid::Scene> scene;

    Internal() : window(hid::sdl::createWindow(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)),
                 context(::createContext(window)),
                 assetManager(::createAssetManager()),
                 data(::createUserData()),
                 renderer(::createRenderer(assetManager)),
                 imgui(std::make_unique<hid::OpenGLImGui>())
    {
    }

    void update(const float &delta)
    {
        getScene().update(delta);
    }

    void render()
    {
        SDL_GL_MakeCurrent(window, context);

        imgui->loop(window);

        getScene().render(renderer);
        imgui->render();

        SDL_GL_SwapWindow(window);
    }

    void init()
    {
        // SDL_AddEventWatch(::resizingEventWatcher, window);

        if (!scene)
        {
            scene = ::createMainScene(*assetManager, data);
        }
        std::function<void()> userImGui = [&]() -> void
        { return data->userImGui(); };

        imgui->setup(window, context);
        imgui->setUserImGui(userImGui);
    }

    hid::Scene &getScene()
    {
        return *scene;
    }
    ~Internal()
    {
        imgui->cleanUp();
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
    }
};

hid::OpenGLApplication::OpenGLApplication() : internal(hid::make_internal_ptr<Internal>()) {}

void hid::OpenGLApplication::render()
{
    internal->render();
}

void hid::OpenGLApplication::init()
{
    internal->init();
}

void hid::OpenGLApplication::update(const float &delta)
{
    internal->update(delta);
}
