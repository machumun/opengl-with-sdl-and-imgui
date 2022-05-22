#pragma once

#include "../../core/internal-ptr.hpp"
#include "../application.hpp"

namespace hid
{
    struct OpenGLApplication : public hid::Application
    {
        OpenGLApplication();
        void update(const float &delta) override;
        void render() override;

        void init() override;

    private:
        struct Internal;
        hid::internal_ptr<Internal> internal;
    };
}