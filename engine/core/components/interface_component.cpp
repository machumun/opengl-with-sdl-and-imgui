#include "interface_component.hpp"

CEREAL_REGISTER_TYPE(hid::IComponent)

using hid::IComponent;

const std::size_t IComponent::Type{std::hash<std::string>()("IComponent")};