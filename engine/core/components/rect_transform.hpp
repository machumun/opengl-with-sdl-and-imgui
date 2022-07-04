#pragma once

#include "interface_component.hpp"
#include "../wrapper/glm_wrapper.hpp"

namespace hid
{
    struct RectTransform : public hid::IComponent
    {
        static const std::size_t Type;
        virtual bool IsClassType(const std::size_t classType) const override
        {
            if (classType == RectTransform::Type)
            {
                return true;
            }
            else
            {
                return hid::IComponent::IsClassType(classType);
            }
        };

        RectTransform(const glm::vec2 &size,
                      const glm::vec2 &position = glm::vec2{.0f, .0f},
                      const glm::vec2 &anchor = glm::vec2{.5f, .5f})
            : size{false},
              position{position},
              anchor{anchor},
              anchoredPosition{anchor + position}
        {
        }

        const glm::vec2 getAnchoredPosition() const
        {
            return anchoredPosition;
        }

    private:
        glm::vec2 size;
        glm::vec2 position;
        glm::vec2 anchoredPosition;
        glm::vec2 anchor;
    };
}