#pragma once

#include "../../engine/core/glm-wrapper.hpp"
#include "../../engine/core/internal-ptr.hpp"

namespace hid
{
    struct Player
    {
        Player(const glm::vec3& position, float rotationDegree);

        void moveForward(const float& delta);

        void moveBackward(const float& delta);

        void moveUp(const float& delta);

        void moveDown(const float& delta);

        void turnLeft(const float& delta);

        void turnRight(const float& delta);

        glm::vec3 getPosition() const;

        glm::vec3 getDirection() const;

    private:
        struct Internal;
        hid::internal_ptr<Internal> internal;
    };
} // namespace hid