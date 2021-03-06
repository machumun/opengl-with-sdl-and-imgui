#pragma once

// #define WIN32

#if defined(__EMSCRIPTEN__)
#include <GLES2/gl2.h>
#elif __APPLE__
#define GL_SILENCE_DEPRECATION
#include "TargetConditionals.h"
#if TARGET_OS_IPHONE
#include <OpenGLES/ES2/gl.h>
#else
#include <OpenGL/gl3.h>
#endif
#elif __ANDROID__
#include <GLES2/gl2.h>
#elif WIN32
#define GLEW_STATIC
#include <GL/glew.h>

#endif

#include <vulkan/vulkan.hpp>
#include <GL/glew.h>