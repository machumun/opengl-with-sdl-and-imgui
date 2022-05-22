#include "opengl-mesh.hpp"
#include "../../core/glm-wrapper.hpp"
#include <vector>

using hid::OpenGLMesh;

namespace
{
    GLuint createVertexBuffer(const hid::Mesh &mesh)
    {
        std::vector<float> bufferData;

        for (const auto &vertex : mesh.getVertices())
        {
            // Position
            bufferData.push_back(vertex.position.x);
            bufferData.push_back(vertex.position.y);
            bufferData.push_back(vertex.position.z);

            // Texture coordinate
            bufferData.push_back(vertex.texCoord.x);
            bufferData.push_back(vertex.texCoord.y);

            bufferData.push_back(vertex.normal.x);
            bufferData.push_back(vertex.normal.y);
            bufferData.push_back(vertex.normal.z);
        }

        GLuint bufferId;
        glGenBuffers(1, &bufferId);
        glBindBuffer(GL_ARRAY_BUFFER, bufferId);
        glBufferData(GL_ARRAY_BUFFER,
                     bufferData.size() * sizeof(float),
                     bufferData.data(),
                     GL_STATIC_DRAW);
        return bufferId;
    }

    GLuint createIndexBuffer(const hid::Mesh &mesh)
    {
        GLuint bufferId;
        glGenBuffers(1, &bufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     mesh.getIndices().size() * sizeof(uint32_t),
                     mesh.getIndices().data(),
                     GL_STATIC_DRAW);

        return bufferId;
    }

    GLuint createVAO()
    {
        GLuint bufferId;
        glGenVertexArrays(1, &bufferId);
        glBindVertexArray(bufferId);
        return bufferId;
    }
    const GLuint ATTRIBUTE_LOCATION_POSITIONS = 0;
    const GLuint ATTRIBUTE_LOCATION_TEXTUREUV = 1;
    const GLuint ATTRIBUTE_LOCATION_NORMALS = 2;
}

struct OpenGLMesh::Internal
{
    // VAO
    const GLuint bufferIdVAO;

    // VBO
    const GLuint bufferIdVertices;

    // EBO
    const GLuint bufferIdIndices;
    const uint32_t numIndices;

    const GLsizei offsetPositionTexCoord;
    const GLsizei offsetTexCoord;
    const GLsizei offsetPositionNormal;
    const GLsizei stride;

    Internal(const hid::Mesh &mesh)
        : bufferIdVertices(::createVertexBuffer(mesh)),
          bufferIdIndices(::createIndexBuffer(mesh)),
          numIndices(static_cast<uint32_t>(mesh.getIndices().size())),
          bufferIdVAO(::createVAO()),
          offsetPositionTexCoord(0),
          offsetTexCoord(3 * sizeof(float)),
          offsetPositionNormal(5 * sizeof(float)),
          stride(8 * sizeof(float))
    {
        glEnableVertexAttribArray(::ATTRIBUTE_LOCATION_POSITIONS);
        glEnableVertexAttribArray(::ATTRIBUTE_LOCATION_TEXTUREUV);
        glEnableVertexAttribArray(::ATTRIBUTE_LOCATION_NORMALS);

        // vbo
        glBindBuffer(GL_ARRAY_BUFFER, bufferIdVertices);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIdIndices);

        glVertexAttribPointer(
            ::ATTRIBUTE_LOCATION_POSITIONS,
            3,
            GL_FLOAT,
            GL_FALSE,
            stride,
            reinterpret_cast<const GLvoid *>(offsetPositionTexCoord));

        glVertexAttribPointer(
            ::ATTRIBUTE_LOCATION_TEXTUREUV,
            2,
            GL_FLOAT,
            GL_FALSE,
            stride,
            reinterpret_cast<const GLvoid *>(offsetTexCoord));

        glVertexAttribPointer(
            ::ATTRIBUTE_LOCATION_NORMALS,
            3,
            GL_FLOAT,
            GL_FALSE,
            stride,
            reinterpret_cast<const GLvoid *>(offsetPositionNormal));

        glBindVertexArray(0);
    }

    ~Internal()
    {
        glDisableVertexAttribArray(::ATTRIBUTE_LOCATION_POSITIONS);
        glDisableVertexAttribArray(::ATTRIBUTE_LOCATION_TEXTUREUV);
        glDisableVertexAttribArray(::ATTRIBUTE_LOCATION_NORMALS);

        glDeleteBuffers(1, &bufferIdVertices);
        glDeleteBuffers(1, &bufferIdIndices);
    }

    // as a mesh renderer
    void draw()
    {
        glBindVertexArray(bufferIdVAO);
        glDrawElements(
            GL_TRIANGLES,
            numIndices,
            GL_UNSIGNED_INT,
            reinterpret_cast<const GLvoid *>(0));
    }
};

OpenGLMesh::OpenGLMesh(const hid::Mesh &mesh) : internal(hid::make_internal_ptr<Internal>(mesh)) {}

const GLuint &OpenGLMesh::getVertexBufferId() const
{
    return internal->bufferIdVertices;
}

const GLuint &OpenGLMesh::getIndexBufferId() const
{
    return internal->bufferIdIndices;
}

const uint32_t &OpenGLMesh::getNumIndices() const
{
    return internal->numIndices;
}

void OpenGLMesh::draw() const
{
    internal->draw();
}