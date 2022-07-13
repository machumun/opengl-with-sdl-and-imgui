#pragma once

#include "../wrapper/glm_wrapper.hpp"
#include "interface_component.hpp"
#include "../log.hpp"

namespace
{
    glm::mat4 computeOrientation(const glm::mat4 &identity, const float &rotationDegrees, const glm::vec3 &up)
    {
        return glm::rotate(identity, glm::radians(rotationDegrees), up);
    }

    glm::vec3 computeForward(const glm::mat4 &orientation)
    {
        return glm::normalize(orientation * glm::vec4(0, 0, 1, 0));
    }
} // namespace

namespace hid
{

    struct Transform : public hid::IComponent
    {
        static const std::size_t Type;
        virtual bool IsClassType(const std::size_t classType) const override;

        const glm::mat4 identity;

        glm::vec3 position;
        glm::vec3 scale;
        glm::vec3 rotationAxis;
        glm::vec3 localEulerAngles;
        float rotationDegrees;
        glm::mat4 transformMatrix;
        glm::mat4 modelMatrix;

        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 forward;

        glm::mat4 orientation;

        Transform(const glm::vec3 &position = glm::vec3{.0f, .0f, .0f},
                  const glm::vec3 &scale = glm::vec3{1.f, 1.f, 1.f},
                  const glm::vec3 &rotationAxis = glm::vec3{.0f, 1.f, .0f},
                  const float &rotationDegrees = .0f)
            : identity{glm::mat4{1.0f}},
              position{position},
              scale{scale},
              rotationAxis{rotationAxis},
              rotationDegrees{rotationDegrees},
              transformMatrix{identity},
              modelMatrix{identity},

              up{glm::vec3{.0f, 1.f, .0f}},
              right{glm::vec3{1.0f, 0.0f, 0.0f}},
              orientation{::computeOrientation(identity, .0f, up)},
              forward{::computeForward(orientation)}
        {
        }

        void update() override;

        void updateModelMatrix();
        void updateForward(const float &rotationDegrees);

        void inspector() override;

        void rotateBy(const float &degrees);

        void setPosition(const glm::vec3 &position);

        glm::mat4 getTransformMatrix() const;
        glm::mat4 getModelMatrix() const;

        template <class Archive>
        void serialize(Archive &archive)
        {
            archive(cereal::base_class<IComponent>(this));
            // archive(cereal::make_nvp("position", position));
            return;
        }
    };
}

CEREAL_REGISTER_TYPE(hid::Transform)
CEREAL_REGISTER_POLYMORPHIC_RELATION(hid::IComponent, hid::Transform)