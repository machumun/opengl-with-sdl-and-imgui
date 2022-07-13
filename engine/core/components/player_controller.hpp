#pragma once

#include "../../application/application.hpp"

#include "camera.hpp"

#include "../wrapper/glm_wrapper.hpp"
#include "../wrapper/sdl_wrapper.hpp"

#include "interface_component.hpp"

#include "../object.hpp"

namespace hid
{

    struct PlayerController : public hid::IComponent
    {

        static const std::size_t Type;
        virtual bool IsClassType(const std::size_t classType) const override;

        const float moveSpeed{5.0f};
        const float turnSpeed{120.0f};

        float rotationDegrees;

        PlayerController() = default;
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

        void start() override;

        void update() override;

        void inspector() override;
    };
} // namespace hid

CEREAL_REGISTER_TYPE(hid::PlayerController)
CEREAL_REGISTER_POLYMORPHIC_RELATION(hid::IComponent, hid::PlayerController)