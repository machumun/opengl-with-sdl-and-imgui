#include "canvas.hpp"
#include "../../application/application.hpp"

#include "../log.hpp"

using hid::Application;
using hid::Canvas;

// CEREAL_REGISTER_TYPE(Canvas);
const std::size_t Canvas::Type = std::hash<std::string>()("Canvas");

void Canvas::graphicRaycaster()
{
    static const std::string logTag{"hid::Canvas::graphicRaycaster"};
}

void Canvas::onAddComponent()
{
    auto &displaySize = hid::sdl::getDisplaySize();
    object->getComponent<RectTransform>().size = glm::vec2{displaySize.first, displaySize.second};
}

Canvas::Canvas() : renderMode{RenderMode::SCREEN_SPACE}
{
}