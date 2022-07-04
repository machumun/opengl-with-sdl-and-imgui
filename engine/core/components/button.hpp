#pragma once

#include "interface_component.hpp"
#include "rect_transform.hpp"
#include "../object.hpp"

namespace hid
{
    struct Button : public hid::IComponent
    {
        static const std::size_t Type;
        virtual bool IsClassType(const std::size_t classType) const override
        {
            if (classType == Button::Type)
            {
                return true;
            }
            else
            {
                return hid::IComponent::IsClassType(classType);
            }
        };

        bool isSelected;
        std::string texture;

        Button()
            : isSelected{false},
              texture{"empty"},
              mesh{"plane"},
              rectTransfrom{&object->getComponent<hid::RectTransform>()}
        {
        }

        void draw() override
        {
        }

    private:
        const std::string mesh;
        hid::RectTransform *rectTransfrom;
    };
}