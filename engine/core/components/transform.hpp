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
              isStatic{false},
              up{glm::vec3{.0f, 1.f, .0f}},
              right{glm::vec3{1.0f, 0.0f, 0.0f}},
              orientation{::computeOrientation(identity, .0f, up)},
              forward{::computeForward(orientation)}
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

        void updateForward(const float &rotationDegrees)
        {
        }

        void inspector()
        {
            if (ImGui::TreeNodeEx((void *)Type, ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
            {
                ImGui::DragFloat3("Position", (float *)&position, 10.f, -10.f);
                ImGui::DragFloat3("Scale", (float *)&scale, 10.f, -10.f);
                ImGui::TreePop();
            }
        }

        void rotateBy(const float &degrees)
        {
            rotationDegrees = degrees;

            if (rotationDegrees > 360.0f)
            {
                rotationDegrees -= 360.0f;
            }
            else if (rotationDegrees < -360.0f)
            {
                rotationDegrees += 360.0f;
            }

            orientation = ::computeOrientation(identity, rotationDegrees, up);
            forward = ::computeForward(orientation);
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