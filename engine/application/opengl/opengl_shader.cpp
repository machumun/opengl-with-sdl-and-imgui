#include "opengl_shader.hpp"
#include "opengl_texture.hpp"

#include "../application.hpp"

#include "../../core/asset_loader.hpp"

#include "../../core/log.hpp"

#include <stdexcept>

using hid::Application;
using hid::OpenGLShader;

namespace
{
    GLuint compileShader(const GLenum &shaderType, const std::string &shaderSource)
    {
        const std::string logTag{"hid::OpenGLShader::compileShader"};

        GLuint shaderId{glCreateShader(shaderType)};

        const char *shaderData{shaderSource.c_str()};
        glShaderSource(shaderId, 1, &shaderData, nullptr);
        glCompileShader(shaderId);

        GLint shaderCompilationResult;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &shaderCompilationResult);

        if (!shaderCompilationResult)
        {
            GLint errorMessageLength;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &errorMessageLength);
            std::vector<char> errorMessage(errorMessageLength + 1);
            glGetShaderInfoLog(shaderId, errorMessageLength, nullptr, &errorMessage[0]);
            hid::log(logTag, &errorMessage[0]);
            throw std::runtime_error(logTag + "Shader failed to compile.");
        }

        return shaderId;
    }

    GLuint createShaderProgram(const std::string &vertShaderName, const std::string &fragShaderName)
    {
        const std::string logTag("hid::OpenGLShader::createShaderProgram");
        hid::log(logTag, "Creating shader program for '" + vertShaderName + "->" + fragShaderName + "'");

        const std::string vertexShaderCode{hid::assets::loadTextFile("assets/shaders/opengl/" + vertShaderName + ".vert")};
        const std::string fragmentShaderCode{hid::assets::loadTextFile("assets/shaders/opengl/" + fragShaderName + ".frag")};

#ifdef USING_GLES
        std::string vertexShaderSource{"#version 100\n" + vertexShaderCode};
        std::string fragmentShaderSource{"#version 100\nprecision mediump float;\n" + fragmentShaderCode};
#else
        std::string vertexShaderSource{"#version 330\n" + vertexShaderCode};
        std::string fragmentShaderSource{"#version 330\n" + fragmentShaderCode};
#endif

        GLuint shaderProgramId{glCreateProgram()};
        GLuint vertexShaderId{::compileShader(GL_VERTEX_SHADER, vertexShaderSource)};
        GLuint fragmentShaderId{::compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource)};

        glAttachShader(shaderProgramId, vertexShaderId);
        glAttachShader(shaderProgramId, fragmentShaderId);
        glLinkProgram(shaderProgramId);

        GLint shaderProgramLinkResult;
        glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &shaderProgramLinkResult);

        if (!shaderProgramLinkResult)
        {
            GLint errorMessageLength;
            glGetProgramiv(shaderProgramId, GL_INFO_LOG_LENGTH, &errorMessageLength);
            std::vector<char> errorMessage(errorMessageLength + 1);
            glGetProgramInfoLog(shaderProgramId, errorMessageLength, nullptr, &errorMessage[0]);
            hid::log(logTag, &errorMessage[0]);
            throw std::runtime_error(logTag + vertShaderName + "Shader program failed to compile.");
        }

        glDetachShader(shaderProgramId, vertexShaderId);
        glDetachShader(shaderProgramId, fragmentShaderId);
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);

        return shaderProgramId;
    }

} // namespace

OpenGLShader::OpenGLShader(const std::string &vertShaderName, const std::string &fragShaderName)
    : shaderProgramId(::createShaderProgram(vertShaderName, fragShaderName)) {}

void OpenGLShader::useProgram() const
{
    glUseProgram(shaderProgramId);
};

void OpenGLShader::release() const
{
    glDeleteProgram(shaderProgramId);
}

GLuint OpenGLShader::resolveUniformLocation(const std::string &name) const
{
    return glGetUniformLocation(shaderProgramId, name.c_str());
}

void OpenGLShader::setBool(const std::string &name, bool value) const
{
    glUniform1i(resolveUniformLocation(name), (int)value);
}
void OpenGLShader::setInt(const std::string &name, int value) const
{
    glUniform1i(resolveUniformLocation(name), value);
}
void OpenGLShader::setFloat(const std::string &name, float value) const
{
    glUniform1f(resolveUniformLocation(name), value);
}

void OpenGLShader::setVec2(const std::string &name, const float *value) const
{
    glUniform2fv(resolveUniformLocation(name), 1, value);
}
void OpenGLShader::setVec3(const std::string &name, const float *value) const
{
    glUniform3fv(resolveUniformLocation(name), 1, value);
}
void OpenGLShader::setVec4(const std::string &name, const float *value) const
{
    glUniform4fv(resolveUniformLocation(name), 1, value);
}

void OpenGLShader::setMat4(const std::string &name, const float *value) const
{
    glUniformMatrix4fv(resolveUniformLocation(name), 1, GL_FALSE, value);
}

void OpenGLShader::setTexture(const std::string &texture) const
{
    glActiveTexture(GL_TEXTURE0);
    Application::assetManager->getTexture(texture)->bind();
}