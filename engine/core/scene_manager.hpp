#pragma once

#include <string>

namespace hid
{
    struct SceneManager
    {
        bool isGameViewFocused;

        SceneManager();

        bool loadScene(const std::string &sceneName);
    };
}