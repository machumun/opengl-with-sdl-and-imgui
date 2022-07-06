#pragma once

#include "interface_component.hpp"
#include "rect_transform.hpp"
#include "canvas.hpp"

#include "../object.hpp"
#include "../wrapper/sdl_wrapper.hpp"

#include <functional>

namespace hid
{
    struct UIButton : public hid::IComponent
    {
        static const std::size_t Type;
        virtual bool IsClassType(const std::size_t classType) const override
        {
            if (classType == UIButton::Type)
            {
                return true;
            }
            else
            {
                return hid::IComponent::IsClassType(classType);
            }
        };

        UIButton(const float &width = 160.f,
                 const float &height = 30.f,
                 const std::string &texture = "empty")
            : isSelected{false},
              texture{texture},
              mesh{"plane"},
              callback{nullptr},
              size{glm::vec2{width, height}},
              pressedColor{glm::vec3{
                  1.f,
                  1.f,
                  1.f}}
        {
        }

        void draw() override;

        void drawEditor() override
        {
        }

        void update() override;

        void start() override;

        void inspector() override
        {
            if (ImGui::TreeNodeEx((void *)Type,
                                  ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_DefaultOpen,
                                  "Button"))
            {
                // ImGui::DragFloat2("View Size", cameraSize, 100.f, 2000.f);
                // ImGui::DragFloat("Angle Of View", &angleOfView, 10.f, 180.f);
                // ImGui::DragFloat2("Near Far", nearfar, .0f, 180.f);
                ImGui::ColorPicker3("Pressed Color", (float *)&pressedColor);
                ImGui::InputText("Texture", &texture);
                ImGui::TreePop();
            }
        }

    private:
        const std::string mesh;
        hid::RectTransform *rectTransfrom;
        hid::Canvas *canvas;
        bool isSelected;
        std::string texture;
        glm::vec2 size;
        std::function<void()> callback;
        glm::vec3 pressedColor;
    };
}