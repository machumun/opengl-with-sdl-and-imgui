#pragma once

#include "../../engine/core/internal-ptr.hpp"
#include "../../engine/core/wrapper/glm_wrapper.hpp"

namespace hid
{
    struct Player
    {

        Player(const glm::vec3& position, float rotationDegree);

        void rotate(const float& amount);

        void moveForward(const float& delta);
        void moveBackward(const float& delta);
        void moveUp(const float& delta);
        void moveDown(const float& delta);
        void turnLeft(const float& delta);
        void turnRight(const float& delta);

        glm::vec3 getPosition() const;

        glm::vec3 getDirection() const;

    private:
        const glm::mat4 identity;
        const glm::vec3 up;
        const float moveSpeed{5.0f};
        const float turnSpeed{120.0f};

        float rotationDegrees;
        glm::vec3 position;
        glm::mat4 orientation;
        glm::vec3 forwardDirection;
        glm::vec3 right;
    };
} // namespace hid