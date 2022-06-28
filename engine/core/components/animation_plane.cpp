#include "animation_plane.hpp"

#include "../log.hpp"

using hid::AnimationPlane;

const std::size_t AnimationPlane::Type = std::hash<std::string>()("AnimationPlane");

void AnimationPlane::update()
{
    static const std::string logTag{"hid::AnimationPlane::update"};

    if (frameCount < skipFrame)
    {
        ++frameCount;
    }
    else
    {
        frameCount = 0;
        ++animationCount;
        if (animationCount == animationFrameSize)
        {
            animationCount = 0;
        }
    }
}
