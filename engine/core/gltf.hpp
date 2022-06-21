#pragma once

#include "json.hpp"
#include "mesh.hpp"
#include "interfaces/IComponent.hpp"
#include "asset_manager.hpp"

using nlohmann::json;

namespace hid
{
    struct GLTF : public hid::IComponent
    {

        GLTF() {}

        // easy access
        const char *file;
        std::vector<unsigned char> data;
        std::string fileDirectory;
        json JSON;

        std::vector<glm::vec3> translationsMeshes;
        std::vector<glm::quat> rotationsMeshes;
        std::vector<glm::vec3> scalesMeshes;

        std::vector<glm::mat4> matricesMeshes;

        std::vector<hid::Mesh> meshes;
        std::vector<std::string> textures;

        void loadMesh(uint32_t indMesh);

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

        void loadTextures();
    };
}