#pragma once

#include "camera.hpp"

#include "../wrapper/glm_wrapper.hpp"
#include "../wrapper/sdl_wrapper.hpp"

#include "../interfaces/interface_component.hpp"

#include "../object.hpp"

namespace hid
{

    struct PlayerController : public hid::IComponent
    {

        static const std::size_t Type;
        virtual bool IsClassType(const std::size_t classType) const override;

        const uint8_t *keyboardState;

        const float moveSpeed{5.0f};
        const float turnSpeed{120.0f};

        float rotationDegrees;

        PlayerController(float rotationDegree);

        void rotate(const float &amount);

        void moveForward(const float &delta);
        void moveBackward(const float &delta);
        void moveUp(const float &delta);
        void moveDown(const float &delta);
        void turnLeft(const float &delta);
        void turnRight(const float &delta);

        void input(const float &delta);

        hid::Transform *transform;

        void start() override
        {
            transform = &parent->getComponent<Transform>();
        }

        void update() override
        {
            transform->rotateBy(rotationDegrees);
        }

        void inspector() override
        {
            if (ImGui::TreeNodeEx((void *)Type,
                                  ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_DefaultOpen,
                                  "Player Controller"))
            {
                ImGui::DragFloat("Move Speed", (float *)&moveSpeed, .0f, 10.f);
                ImGui::DragFloat("Turn Speed", (float *)&turnSpeed, .0f, 240.f);
                ImGui::DragFloat("Rotation Degrees", (float *)&turnSpeed, .0f, 240.f);
                ImGui::TreePop();
            }
        }
    };
} // namespace hid