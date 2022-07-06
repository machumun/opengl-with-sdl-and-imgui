#pragma once

#include "interface_component.hpp"

#include "../wrapper/sdl_wrapper.hpp"
#include "../wrapper/glm_wrapper.hpp"

#include "../object.hpp"

namespace hid
{
    enum class RenderMode
    {
        SCREEN_SPACE
    };
    struct Canvas : public hid::IComponent
    {
        static const std::size_t Type;
        virtual bool IsClassType(const std::size_t classType) const override
        {
            if (classType == Canvas::Type)
            {
                return true;
            }
            else
            {
                return hid::IComponent::IsClassType(classType);
            }
        };

        RenderMode renderMode;

        void graphicRaycaster();

        // uint32_t x, y;
        // std::pair<uint32_t, uint32_t> hid::sdl::getDisplaySize();
        Canvas() : renderMode{RenderMode::SCREEN_SPACE}
        {
        }

        void start() override
        {
            auto &displaySize = hid::sdl::getDisplaySize();
            object->getComponent<RectTransform>().size = glm::vec2{displaySize.first, displaySize.second};
        }

        void inspector() override
        {
            if (ImGui::TreeNodeEx((void *)Type,
                                  ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_DefaultOpen,
                                  "Canvas"))
            {
                // ImGui::DragFloat2("View Size", cameraSize, 100.f, 2000.f);
                // ImGui::DragFloat("Angle Of View", &angleOfView, 10.f, 180.f);
                // ImGui::DragFloat2("Near Far", nearfar, .0f, 180.f);
                // ImGui::ColorPicker3("Background Color", (float *)&background);
                // ImGui::Combo();
                ImGui::TreePop();
            }
        }

        void update() override
        {
            graphicRaycaster();
        }
    };
}