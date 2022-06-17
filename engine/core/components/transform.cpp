#include "transform.hpp"

using hid::Transform;

const std::size_t Transform::Type{std::hash<std::string>()("Transform")};

bool Transform::IsClassType(const std::size_t classType) const
{
    if (classType == Transform::Type)
    {
        return true;
    }
    else
    {
        return hid::IComponent::IsClassType(classType);
    }
}