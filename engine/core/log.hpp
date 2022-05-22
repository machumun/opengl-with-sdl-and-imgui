#pragma once

#include <string>


namespace hid
{
    void log(const std::string &tag, const std::string &message);
    void log(const std::string &tag, const std::string &message, const std::exception &error);
}