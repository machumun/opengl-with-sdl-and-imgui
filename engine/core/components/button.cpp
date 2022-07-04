#include "button.hpp"

#include "../log.hpp"

using hid::Button;

const std::size_t Button::Type = std::hash<std::string>()("Button");