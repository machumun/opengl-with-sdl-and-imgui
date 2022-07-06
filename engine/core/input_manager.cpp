#include "input_manager.hpp"

#include <cstring>

using hid::InputManager;

bool InputManager::keyDown(SDL_Scancode scanCode)
{
    return keyboardState[scanCode];
}

bool InputManager::keyPressed(SDL_Scancode scanCode)
{
    return !prevKeyboardState[scanCode] && keyboardState[scanCode];
}

bool InputManager::keyReleased(SDL_Scancode scanCode)
{
    return prevKeyboardState[scanCode] && !keyboardState[scanCode];
}

bool InputManager::mouseButtonDown(const MouseButtons &button)
{
    uint32_t mask = 0;

    switch (button)
    {
    case MouseButtons::LEFT:
        mask = SDL_BUTTON_LMASK;
        break;
    case MouseButtons::RIGHT:
        mask = SDL_BUTTON_RMASK;
        break;
    case MouseButtons::MIDDLE:
        mask = SDL_BUTTON_MMASK;
        break;
    case MouseButtons::BACK:
        mask = SDL_BUTTON_X1MASK;
        break;
    case MouseButtons::FORWARD:
        mask = SDL_BUTTON_X2MASK;
        break;
    }
    return (mouseState & mask);
}

bool InputManager::mouseButtonPressed(const MouseButtons &button)
{
    uint32_t mask = 0;

    switch (button)
    {
    case MouseButtons::LEFT:
        mask = SDL_BUTTON_LMASK;
        break;
    case MouseButtons::RIGHT:
        mask = SDL_BUTTON_RMASK;
        break;
    case MouseButtons::MIDDLE:
        mask = SDL_BUTTON_MMASK;
        break;
    case MouseButtons::BACK:
        mask = SDL_BUTTON_X1MASK;
        break;
    case MouseButtons::FORWARD:
        mask = SDL_BUTTON_X2MASK;
        break;
    }
    return !(prevMouseState & mask) && (mouseState & mask);
}

bool InputManager::mouseButtonReleased(const MouseButtons &button)
{
    uint32_t mask = 0;

    switch (button)
    {
    case MouseButtons::LEFT:
        mask = SDL_BUTTON_LMASK;
        break;
    case MouseButtons::RIGHT:
        mask = SDL_BUTTON_RMASK;
        break;
    case MouseButtons::MIDDLE:
        mask = SDL_BUTTON_MMASK;
        break;
    case MouseButtons::BACK:
        mask = SDL_BUTTON_X1MASK;
        break;
    case MouseButtons::FORWARD:
        mask = SDL_BUTTON_X2MASK;
        break;
    }
    return (prevMouseState & mask) && !(mouseState & mask);
}

void InputManager::update()
{
    mouseState = SDL_GetMouseState(&pointerX, &pointerY);
}

void InputManager::updatePrevInput()
{
    memcpy(prevKeyboardState, keyboardState, keyLength);
    prevMouseState = mouseState;
}