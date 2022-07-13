#pragma once

#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

#include <string>
#include <memory>
#include <vector>

#include <cereal/types/base_class.hpp>
#include <cereal/types/memory.hpp>

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
        ~IComponent() = default;

        virtual void updateEditor() {}

        virtual void update() {}
        virtual void start() {}

        virtual void drawEditor() {}
        virtual void draw() {}

        virtual void onAddComponent() {}

        // virtual void draw() {}

        virtual void inspector() {}

        template <class Archive>
        void serialize(Archive &archive)
        {
            return;
        }
    };
}