#include "player_controller.hpp"

#include "../../application/application.hpp"

using hid::Application;
using hid::PlayerController;

const std::size_t PlayerController::Type = std::hash<std::string>()("PlayerController");
bool PlayerController::IsClassType(const std::size_t classType) const
{
    if (classType == PlayerController::Type)
    {
        return true;
    }
    else
    {
        return hid::IComponent::IsClassType(classType);
    }
}

PlayerController::PlayerController(float rotationDegrees)
    : rotationDegrees{rotationDegrees}
{
}

void PlayerController::moveForward(const float &delta)
{
    transform->position -= transform->forward * (moveSpeed * delta);
}

void PlayerController::moveBackward(const float &delta)
{
    transform->position += transform->forward * (moveSpeed * delta);
}

void PlayerController::turnLeft(const float &delta)
{
    rotate(turnSpeed * delta);
}

void PlayerController::turnRight(const float &delta)
{
    rotate(-turnSpeed * delta);
}

void PlayerController::moveUp(const float &delta)
{
    transform->position.y += (moveSpeed * delta);
}

void PlayerController::moveDown(const float &delta)
{
    transform->position.y -= (moveSpeed * delta);
}

void PlayerController::rotate(const float &amount)
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
}

void PlayerController::input(const float &delta)
{
    if (Application::inputManager->keyDown(SDL_SCANCODE_UP))
    {
        moveForward(delta);
    }

    if (Application::inputManager->keyDown(SDL_SCANCODE_DOWN))
    {
        moveBackward(delta);
    }

    if (Application::inputManager->keyDown(SDL_SCANCODE_A))
    {
        moveUp(delta);
    }

    if (Application::inputManager->keyDown(SDL_SCANCODE_Z))
    {
        moveDown(delta);
    }

    if (Application::inputManager->keyDown(SDL_SCANCODE_LEFT))
    {
        turnLeft(delta);
    }

    if (Application::inputManager->keyDown(SDL_SCANCODE_RIGHT))
    {
        turnRight(delta);
    }
}

void PlayerController::start()
{
    transform = object->transform;
}

void PlayerController::update()
{
    input(Application::timeStep());
    transform->rotateBy(rotationDegrees);
}

void PlayerController::inspector()
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
