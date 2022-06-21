#pragma once

#include "../glm-wrapper.hpp"
#include "../interfaces/IComponent.hpp"
#include "../log.hpp"

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

        bool isStatic;

        // TransformComponent() = default;
        // TransformComponent(const TransformComponent &) = default;
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
              isStatic{false}
        {
        }

        void update()
        {
            const static std::string logTag{"hid::Transform::update"};

            if (!isStatic)
            {
                // hid::log(logTag, "update matrix");
                updateModelMatrix();
            }
        }

        void updateModelMatrix()
        {
            modelMatrix = glm::translate(identity, position) *
                          glm::rotate(identity, glm::radians(rotationDegrees), rotationAxis) *
                          glm::scale(identity, scale);
        }

        void rotateBy(const float &degrees)
        {
            rotationDegrees += degrees;

            if (rotationDegrees > 360.0f)
            {
                rotationDegrees -= 360.0f;
            }
            else if (rotationDegrees < -360.0f)
            {
                rotationDegrees += 360.0f;
            }
        }

        void setPosition(const glm::vec3 &position)
        {
            this->position = position;
        }

        // void setProjectionMatrix(const ){}

        glm::mat4 getTransformMatrix() const
        {
            return transformMatrix;
        }

        glm::mat4 getModelMatrix() const
        {
            return modelMatrix;
        }
    };
}