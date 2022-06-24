#include "light.hpp"

using hid::Light;

const std::size_t Light::Type = std::hash<std::string>()("Light");
