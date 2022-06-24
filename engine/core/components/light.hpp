#pragma once

#include "transform.hpp"

#include "interface_component.hpp"
#include "../wrapper/glm_wrapper.hpp"

#include "../object.hpp"

namespace hid
{
    enum class LightType
    {
        Point,
        Ambient,
        Directional
    };

    struct Light : public IComponent
    {

        static const std::size_t Type;
        virtual bool IsClassType(const std::size_t classType) const override
        {
            if (classType == Light::Type)
            {
                return true;
            }
            else
            {
                return hid::IComponent::IsClassType(classType);
            }
        };

        LightType lightType;
        glm::vec3 color;
        float intensity;

        hid::Transform *transform;

        Light(
            const LightType &lightType,
            const glm::vec3 &color = glm::vec3{1.0f, 1.0f, 1.0f},
            const float &intensity = 1.0f)
            : lightType{lightType},
              color{color},
              intensity{intensity} {};

        void setColor(const glm::vec3 &color) { this->color = color; }
        void setIntensity(float &intensity) { this->intensity = intensity; }

        void start() override
        {
            transform = &parent->getComponent<hid::Transform>();
        }

        void inspector() override
        {
            if (ImGui::TreeNodeEx((void *)Type,
                                  ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_DefaultOpen,
                                  "Light"))
            {
                // ImGui::InputText("Type", &type);
                ImGui::DragFloat("Intencity", &intensity);
                ImGui::ColorPicker3("Color", (float *)&color);
                ImGui::TreePop();
            }
        }
    };
}