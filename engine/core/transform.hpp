#pragma once

#include "asset-inventory.hpp"
#include "glm-wrapper.hpp"
#include "internal-ptr.hpp"
#include "material.hpp"

namespace hid
{
    struct Transform
    {

        const glm::mat4 identity;

        glm::vec3 position;
        glm::vec3 scale;
        glm::vec3 rotationAxis;
        float rotationDegrees;
        glm::mat4 transformMatrix;
        glm::mat4 modelMatrix;

        Transform(const glm::vec3 &position,
                  const glm::vec3 &scale,
                  const glm::vec3 &rotationAxis,
                  const float &rotationDegrees)
            : identity(glm::mat4{1.0f}),
              position(position),
              scale(scale),
              rotationAxis(rotationAxis),
              rotationDegrees(rotationDegrees),
              transformMatrix(identity),
              modelMatrix(identity)
        {
        }

        void update(const glm::mat4 &projectionViewMatrix)
        {

            transformMatrix = projectionViewMatrix *
                              glm::translate(identity, position) *
                              glm::rotate(identity, glm::radians(rotationDegrees), rotationAxis) *
                              glm::scale(identity, scale);
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
