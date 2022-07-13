#include "ui_image.hpp"

using hid::UIImage;

// CEREAL_REGISTER_TYPE(UIImage);
const std::size_t UIImage::Type = std::hash<std::string>()("UIImage");