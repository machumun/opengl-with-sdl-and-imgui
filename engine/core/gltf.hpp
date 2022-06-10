#pragma once

#include "json.hpp"
#include "mesh.hpp"
#include "bitmap.hpp"
#include "transform.hpp"

using nlohmann::json;

namespace hid
{
    struct GLTF : public hid::Transform
    {

        GLTF(
            const glm::vec3 &position = glm::vec3{0.0f, 0.0f, 0.0f},
            const glm::vec3 &scale = glm::vec3{1.0f, 1.0f, 1.0f},
            const glm::vec3 &rotationAxis = glm::vec3{0.0f, 1.0f, 0.0f},
            const float &rotationDegrees = 0.0f)
            : Transform(position, scale, rotationAxis, rotationDegrees){};

        // easy access
        const char *file;
        std::vector<unsigned char> data;
        json JSON;

        std::vector<std::string> loadedTexName;
        std::vector<hid::Bitmap> loadedTex;

        std::vector<glm::vec3> translationsMeshes;
        std::vector<glm::quat> rotationsMeshes;
        std::vector<glm::vec3> scalesMeshes;

        std::vector<hid::Transform> transformMeshes;
        std::vector<glm::mat4> matricesMeshes;

        std::vector<hid::Mesh> meshes;
        void loadMash(uint32_t indMesh);

        // GLTF();

        std::vector<unsigned char> getData();
        std::vector<float> getFloats(json accessor);
        std::vector<uint32_t> getIndices(json accessor);
        std::vector<hid::Vertex> assembleVertices(
            std::vector<glm::vec3> positions,
            std::vector<glm::vec3> normals,
            std::vector<glm::vec2> texUVs);

        void traverseNode(const uint32_t &nextNode, const glm::mat4 &matrix = glm::mat4{1.0f});

        std::vector<glm::vec2> groupFloatsVec2(const std::vector<float> &floatVec);
        std::vector<glm::vec3> groupFloatsVec3(const std::vector<float> &floatVec);
        std::vector<glm::vec4> groupFloatsVec4(const std::vector<float> &floatVec);

        std::vector<hid::Bitmap> getTextures();
    };
}