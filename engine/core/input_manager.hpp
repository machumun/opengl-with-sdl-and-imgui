#pragma once

#include "wrapper/sdl_wrapper.hpp"
#include "wrapper/glm_wrapper.hpp"

#include "wrapper/glm_wrapper.hpp"

namespace hid
{
    enum MouseEvent : uint8_t
    {
        MOUSE_BUTTON_DOWN = 1 << 0,
        MOUSE_BUTTON_RELEASED = 1 << 1,
        MOUSE_BUTTON_PRESSED = 1 << 2
    };

    enum MouseButtons : uint8_t
    {
        LEFT = 1 << 0,
        RIGHT = 1 << 1,
        MIDDLE = 1 << 2,
        BACK = 1 << 3,
        FORWARD = 1 << 4
    };

    struct InputManager
    {

        int keyLength;
        const uint8_t *keyboardState;
        uint8_t *prevKeyboardState;

        // mouse or touch
        int pointerX, pointerY;

        uint32_t mouseState;
        uint32_t prevMouseState;

        InputManager()
            : keyboardState{SDL_GetKeyboardState(&keyLength)},
              mouseState{0},
              prevMouseState{0}
        {
            prevKeyboardState = new uint8_t[keyLength];
            memcpy(prevKeyboardState, keyboardState, keyLength);
        }

        ~InputManager()
        {
            delete[] prevKeyboardState;
        }

        void update();

        void updatePrevInput();

        bool keyDown(SDL_Scancode scanCode);
        bool keyPressed(SDL_Scancode scanCode);
        bool keyReleased(SDL_Scancode scanCode);

        void mousePress();
        void mouseUp();

        bool mouseButtonPressed(const MouseButtons &button);
        bool mouseButtonDown(const MouseButtons &button);
        bool mouseButtonReleased(const MouseButtons &button);

        bool clearInput()
        {
            mouseState = 0;
        }

        glm::vec2 getMousePos()
        {
            return glm::vec2{pointerX, pointerY};
        }

        // in using
        // if(mouseEvent & MOUSE_BUTTON_DOWN){}
    };
}