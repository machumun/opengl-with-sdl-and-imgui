#include "interface_component.hpp"

using hid::IComponent;

const std::size_t IComponent::Type{std::hash<std::string>()("IComponent")};