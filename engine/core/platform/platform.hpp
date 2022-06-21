#pragma once


namespace hid
{
    enum class Platform
    {
        mac,
        ios,
        android,
        windows
    };
    Platform getCurrentPlatform();
}