#pragma once

#include <string>
#include "wrapper/graphics_wrapper.hpp"

namespace hid
{
    struct Shader
    {

        virtual void use() const = 0;
        virtual void setBool(const std::string &name, bool value) const = 0;
        virtual void setInt(const std::string &name, int value) const = 0;
        virtual void setFloat(const std::string &name, float value) const = 0;

        virtual void setVec2(const std::string &name, const float *value) const = 0;
        virtual void setVec3(const std::string &name, const float *value) const = 0;
        virtual void setVec4(const std::string &name, const float *value) const = 0;
        virtual void setMat4(const std::string &name, const float *value) const = 0;

        virtual void release() const = 0;

        static Shader *create(const std::string &vertShaderName, const std::string &fragShaderName);
    };
}