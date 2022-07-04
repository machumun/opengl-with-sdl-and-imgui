#pragma once

#include "interface_component.hpp"
#include "../material.hpp"

#include "../object.hpp"

namespace hid
{
    struct Camera : public hid::IComponent
    {
        static const std::size_t Type;
        virtual bool IsClassType(const std::size_t classType) const override
        {
            if (classType == Camera::Type)
            {
                return true;
            }
            else
            {
                return hid::IComponent::IsClassType(classType);
            }
        };

        glm::mat4 projectionMatrix;
        float cameraSize[2];
        float angleOfView;
        float nearfar[2];

        glm::vec3 background;

        hid::Transform *transform;

        Camera(const float &width, const float &height)
            : projectionMatrix{glm::mat4{1.f}},
              cameraSize{width, height},
              angleOfView{60.f},
              nearfar{.01f, 100.f},
              background{glm::vec3{
                  .3f,
                  .3f,
                  .3f}}
        {
        }

        glm::mat4 Camera::getProjectionMatrix() const
        {
            return projectionMatrix;
        }

        glm::mat4 Camera::getViewMatrix() const
        {
            return glm::lookAt(transform->position,
                               transform->position - transform->forward,
                               transform->up);
        }

        glm::mat4 Camera::getCameraMatrix() const
        {
            return getProjectionMatrix() * getViewMatrix();
        };

        void inspector() override
        {
            if (ImGui::TreeNodeEx((void *)Type, ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
            {
                ImGui::DragFloat2("View Size", cameraSize, 100.f, 2000.f);
                ImGui::DragFloat("Angle Of View", &angleOfView, 10.f, 180.f);
                ImGui::DragFloat2("Near Far", nearfar, .0f, 180.f);
                ImGui::ColorPicker3("Background Color", (float *)&background);
                ImGui::TreePop();
            }
        }

        void start() override
        {
            transform = object->transform;
        }

        void update() override
        {
            projectionMatrix = glm::perspective(glm::radians(angleOfView), cameraSize[0] / cameraSize[1], nearfar[0], nearfar[1]);
        }
    };
}
