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
            : size{size},
              position{position},
              anchor{anchor}
        {
        }

        const glm::vec2 getAnchoredPosition() const
        {
            return anchor + position;
        }

        void inspector() override
        {
            if (ImGui::TreeNodeEx((void *)Type,
                                  ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_DefaultOpen,
                                  "Rect Transform"))
            {
                ImGui::DragFloat2("Position", (float *)&position);
                ImGui::DragFloat2("Size", (float *)&size);
                ImGui::DragFloat2("Anchor", (float *)&anchor, 1.f, .0f);
                ImGui::TreePop();
            }
        }

        glm::vec2 size;
        glm::vec2 position;
        glm::vec2 anchor;
    };
}