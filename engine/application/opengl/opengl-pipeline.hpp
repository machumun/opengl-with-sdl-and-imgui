#pragma once

#include "../../core/internal-ptr.hpp"
#include "../../core/light-settings.hpp"
#include "../../core/gui/gui.hpp"
#include "../../core/perspective-camera.hpp"
#include <string>
#include <vector>

namespace hid
{
    struct OpenGLAssetManager;

    struct OpenGLPipeline
    {
        OpenGLPipeline(const std::string &vertShaderName, const std::string &fragShaderName);

        // unlit

        void render(
            const hid::OpenGLAssetManager &assetManager,
            const std::shared_ptr<hid::Gui> &userData,
            const hid::PerspectiveCamera &cameras);

    private:
        struct Internal;
        hid::internal_ptr<Internal> internal;
    };
}