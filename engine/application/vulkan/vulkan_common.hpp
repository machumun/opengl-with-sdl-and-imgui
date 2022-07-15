#pragma once

#include <string>
#include <vector>

namespace hid::vulkan
{
    std::vector<std::string> getRequiredVulkanExtensionNames();
    bool isVulkanAvailable();
}