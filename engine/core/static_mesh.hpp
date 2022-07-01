#pragma once

namespace hid
{
    struct StaticMesh
    {
        virtual void draw() const = 0;
    };
}