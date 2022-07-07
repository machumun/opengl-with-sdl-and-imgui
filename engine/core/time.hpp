#pragma once

namespace hid
{
    struct Time
    {
        float deltaTime;

        Time() : deltaTime{.0f} {}
    };
}