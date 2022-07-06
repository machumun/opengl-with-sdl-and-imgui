#include "ui_button.hpp"

#include "../log.hpp"

using hid::UIButton;

const std::size_t UIButton::Type = std::hash<std::string>()("UIButton");

void UIButton::update()
{
}

void UIButton::start()
{
    rectTransfrom = &object->getComponent<hid::RectTransform>();
    canvas = &object->parent->getComponent<Canvas>();

    rectTransfrom->size = size;
}

void UIButton::draw()
{
}