#pragma once

#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

#include <string>
#include <memory>
#include <vector>

namespace hid
{
    struct Object;

    struct IComponent
    {
        static const std::size_t Type;
        hid::Object *object;

        virtual bool IsClassType(const std::size_t classType) const
        {
            return classType == Type;
        }

        // Do not load &object in constructor.
        IComponent() = default;
        virtual ~IComponent() = default;

        virtual void updateEditor() {}

        virtual void update() {}
        virtual void start() {}

        virtual void drawEditor() {}
        virtual void draw() {}

        virtual void onAddComponent() {}

        // virtual void draw() {}

        virtual void inspector() {}
    };
}