#pragma once

#include "interface_component.hpp"
#include "../material.hpp"

#include "../object.hpp"

#include <utility>

namespace hid
{
    struct AnimationPlane : public hid::IComponent
    {
        static const std::size_t Type;
        virtual bool IsClassType(const std::size_t classType) const override
        {
            if (classType == AnimationPlane::Type)
            {
                return true;
            }
            else
            {
                return hid::IComponent::IsClassType(classType);
            }
        };

        std::string mesh;
        const std::vector<uint32_t> *animationFrame;
        const size_t animationFrameSize;
        const uint32_t animationInterval;
        const std::pair<uint32_t, uint32_t> spriteSize;
        hid::Material material;

        uint32_t animationCount;

        AnimationPlane(
            const hid::Material &material,
            const std::vector<uint32_t> *animationFrame,
            const uint32_t &animationInterval,
            const uint32_t &spriteWidth,
            const uint32_t &spriteHeight)
            : mesh{"plane"},
              animationFrame{animationFrame},
              animationFrameSize{animationFrame->size()},
              animationInterval{animationInterval},
              spriteSize{spriteWidth, spriteHeight},
              material{material},
              animationCount{0}
        {
            parent->transform->rotationDegrees = 90.f;
        };

        hid::Material getMaterial() const
        {
            return material;
        }
    };
}