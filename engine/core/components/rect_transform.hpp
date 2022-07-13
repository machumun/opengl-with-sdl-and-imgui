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

        RectTransform(const glm::vec2 &size = glm::vec2{160.f, 30.f},
                      const glm::vec2 &position = glm::vec2{.0f, .0f},
                      const glm::vec2 &anchor = glm::vec2{.5f, .5f})
            : identity{glm::mat4{1.f}},
              size{size},
              position{position},
              anchor{anchor},
              scale{glm::vec2{1.0f, 1.0f}},
              rotationAxis{glm::vec3{1.f, .0f, .0f}},
              rotationDegrees{.0f}
        {
        }

        const glm::vec2 getAnchoredPosition() const
        {
            return anchor + position;
        }

        void inspector() override;
        void updateModelMatrix();
        void update() override;
        glm::mat4 getModelMatrix() const;
        void start() override;

        glm::vec2 size;
        static glm::vec2 unitPerDisplaySize;
        glm::vec2 position;
        glm::vec2 anchor;
        glm::vec2 scale;
        const glm::mat4 identity;
        glm::mat4 modelMatrix;
        const glm::vec3 rotationAxis;
        float rotationDegrees;
    };
}

CEREAL_REGISTER_TYPE(hid::RectTransform)
CEREAL_REGISTER_POLYMORPHIC_RELATION(hid::IComponent, hid::RectTransform)