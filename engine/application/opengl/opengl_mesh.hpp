#pragma once
#include "../../core/wrapper/graphics_wrapper.hpp"
#include "../../core/mesh.hpp"
#include "../../core/static_mesh.hpp"

namespace hid
{

    struct OpenGLMesh : public hid::StaticMesh
    {
        // VAO
        const GLuint bufferIdVAO;

        // VBO
        const GLuint bufferIdVBO;

        // EBO
        const GLuint bufferIdEBO;
        const uint32_t numIndices;

        const GLsizei offsetPositionTexCoord;
        const GLsizei offsetTexCoord;
        const GLsizei offsetPositionNormal;
        const GLsizei stride;

        OpenGLMesh(const hid::Mesh &mesh);
        ~OpenGLMesh();

        void draw() const override;
    };
}