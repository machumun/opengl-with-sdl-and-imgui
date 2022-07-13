#pragma once

#include "interface_component.hpp"

namespace hid
{

    struct UIImage : public IComponent
    {
        static const std::size_t Type;
        virtual bool IsClassType(const std::size_t classType) const override
        {
            if (classType == UIImage::Type)
            {
                return true;
            }
            else
            {
                return hid::IComponent::IsClassType(classType);
            }
        };
    };
}

CEREAL_REGISTER_TYPE(hid::UIImage)
CEREAL_REGISTER_POLYMORPHIC_RELATION(hid::IComponent, hid::UIImage)