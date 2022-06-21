#pragma once

#include "../../core/shader.hpp"
#include "../../core/internal-ptr.hpp"

namespace hid
{
    struct OpenGLShader : public hid::Shader
    {
        const GLuint shaderProgramId;
        OpenGLShader(const std::string &vertShaderName, const std::string &fragShaderName);

        void use() const override;
        void release() const override;

        void setBool(const std::string &name, bool value) const override;
        void setInt(const std::string &name, int value) const override;
        void setFloat(const std::string &name, float value) const override;

        void setMat4(const std::string &name, const float *value) const override;
        void setVec2(const std::string &name, const float *value) const override;
        void setVec3(const std::string &name, const float *value) const override;
        void setVec4(const std::string &name, const float *value) const override;

        GLuint getShaderProgramId() const;
        GLuint resolveUniformLocation(const std::string &name) const;
    };
}