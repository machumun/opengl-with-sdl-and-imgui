#include "canvas.hpp"
#include "../../application/application.hpp"

#include "../log.hpp"

using hid::Application;
using hid::Canvas;

const std::size_t Canvas::Type = std::hash<std::string>()("Canvas");

void Canvas::graphicRaycaster()
{
    static const std::string logTag{"hid::Canvas::graphicRaycaster"};

    // hid::log(logTag, std::to_string(Application::inputManager->buttons & SDL_BUTTON_LMASK));
    // hid::log(logTag, std::to_string(SDL_BUTTON_MMASK));
    // hid::log(logTag, std::to_string(SDL_BUTTON_RMASK));
    // hid::log(logTag, std::to_string(SDL_BUTTON_X1MASK));
    // hid::log(logTag, std::to_string(SDL_BUTTON_X2MASK));

    if (Application::inputManager->mouseButtonPressed(MouseButtons::LEFT))
    {
        // auto mousePosition = Application::inputManager->getMousePos();
        // hid::log(logTag, "Plessed left mouse btn.X: " + std::to_string(mousePosition.x));
    }
    if (Application::inputManager->mouseButtonReleased(MouseButtons::LEFT))
    {
        hid::log(logTag, "Up mouse btn.");
    }
}

void Canvas::onAddComponent()
{
    auto &displaySize = hid::sdl::getDisplaySize();
    object->getComponent<RectTransform>().size = glm::vec2{displaySize.first, displaySize.second};
}