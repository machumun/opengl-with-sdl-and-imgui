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

        Light() = default;
        Light(
            const LightType &lightType,
            const glm::vec3 &color,
            const float &intensity);

        void setColor(const glm::vec3 &color) { this->color = color; }
        void setIntensity(float &intensity) { this->intensity = intensity; }

        void start() override
        {
            transform = object->transform;
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

CEREAL_REGISTER_TYPE(hid::Light)
CEREAL_REGISTER_POLYMORPHIC_RELATION(hid::IComponent, hid::Light)