#include "player.hpp"

using hid::Player;

namespace
{
    glm::mat4 computeOrientation(const glm::mat4& identity, const float& rotationDegrees, const glm::vec3& up)
    {
        return glm::rotate(identity, glm::radians(rotationDegrees), up);
    }

    glm::vec3 computeForwardDirection(const glm::mat4& orientation)
    {
        return glm::normalize(orientation * glm::vec4(0, 0, 1, 0));
    }
} // namespace

Player::Player(const glm::vec3& position, float rotationDegrees)
    : identity(glm::mat4(1)),
      up(glm::vec3{0.0f, 1.0f, 0.0f}),
      right(glm::vec3{1.0f, 0.0f, 0.0f}),
      rotationDegrees(rotationDegrees),
      position(position),
      orientation(::computeOrientation(identity, rotationDegrees, up)),
      forwardDirection(::computeForwardDirection(orientation)) {}

void Player::moveForward(const float& delta)
{
    position -= forwardDirection * (moveSpeed * delta);
}

void Player::moveBackward(const float& delta)
{
    position += forwardDirection * (moveSpeed * delta);
}

void Player::turnLeft(const float& delta)
{
    rotate(turnSpeed * delta);
}

void Player::turnRight(const float& delta)
{
    rotate(-turnSpeed * delta);
}

void Player::moveUp(const float& delta)
{
    position.y += (moveSpeed * delta);
}

void Player::moveDown(const float& delta)
{
    position.y -= (moveSpeed * delta);
}

void Player::rotate(const float& amount)
{
    rotationDegrees += amount;

    if (rotationDegrees > 360.0f)
    {
        rotationDegrees -= 360.0f;
    }
    else if (rotationDegrees < 0.0f)
    {
        rotationDegrees += 360.0f;
    }

    orientation = ::computeOrientation(identity, rotationDegrees, up);
    forwardDirection = ::computeForwardDirection(orientation);
}

glm::vec3 Player::getPosition() const
{
    return position;
}

glm::vec3 Player::getDirection() const
{
    return forwardDirection;
}
