#include "gltf.hpp"
#include "assets.hpp"
#include "log.hpp"
// #include "sdl-wrapper.hpp"

using hid::GLTF;

// GLTF::GLTF()
// {
// }

std::vector<unsigned char> GLTF::getData()
{
    return data;
}

std::vector<float> GLTF::getFloats(json accessor)
{
    std::vector<float> floatVec;

    uint32_t buffViewInd = accessor.value("bufferView", 1);
    uint32_t count = accessor["count"];
    uint32_t accByteOffset = accessor.value("byteOffset", 0);
    std::string type = accessor["type"];

    json bufferView = JSON["bufferViews"][buffViewInd];
    uint32_t byteOffset = bufferView["byteOffset"];

    uint32_t numPerVert;
    if (type == "SCALAR")
        numPerVert = 1;
    else if (type == "VEC2")
        numPerVert = 2;
    else if (type == "VEC3")
        numPerVert = 3;
    else if (type == "VEC4")
        numPerVert = 4;
    else
        throw std::invalid_argument("Type is invalid (not SCALAR, VEC2, VEC3, or VEC4)");

    // Go over all the bytes in the data at the correct place using the properties from above
    uint32_t beginningOfData = byteOffset + accByteOffset;
    uint32_t lengthOfData = count * 4 * numPerVert;
    for (uint32_t i = beginningOfData; i < beginningOfData + lengthOfData; i)
    {
        unsigned char bytes[] = {data[i++], data[i++], data[i++], data[i++]};
        float value;
        std::memcpy(&value, bytes, sizeof(float));
        floatVec.push_back(value);
    }

    return floatVec;
}

std::vector<uint32_t> GLTF::getIndices(json accessor)
{
    std::vector<uint32_t> indices;

    // Get properties from the accessor
    uint32_t buffViewInd = accessor.value("bufferView", 0);
    uint32_t count = accessor["count"];
    uint32_t accByteOffset = accessor.value("byteOffset", 0);
    uint32_t componentType = accessor["componentType"];

    // Get properties from the bufferView
    json bufferView = JSON["bufferViews"][buffViewInd];
    uint32_t byteOffset = bufferView["byteOffset"];

    // Get indices with regards to their type: uint32_t, unsigned short, or short
    uint32_t beginningOfData = byteOffset + accByteOffset;
    if (componentType == 5125)
    {
        for (uint32_t i = beginningOfData; i < byteOffset + accByteOffset + count * 4; i)
        {
            unsigned char bytes[] = {data[i++], data[i++], data[i++], data[i++]};
            uint32_t value;
            std::memcpy(&value, bytes, sizeof(uint32_t));
            indices.push_back((uint32_t)value);
        }
    }
    else if (componentType == 5123)
    {
        for (uint32_t i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i)
        {
            unsigned char bytes[] = {data[i++], data[i++]};
            unsigned short value;
            std::memcpy(&value, bytes, sizeof(unsigned short));
            indices.push_back((uint32_t)value);
        }
    }
    else if (componentType == 5122)
    {
        for (uint32_t i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i)
        {
            unsigned char bytes[] = {data[i++], data[i++]};
            short value;
            std::memcpy(&value, bytes, sizeof(short));
            indices.push_back((uint32_t)value);
        }
    }

    return indices;
}

std::vector<hid::Vertex> GLTF::assembleVertices(
    std::vector<glm::vec3> positions,
    std::vector<glm::vec3> normals,
    std::vector<glm::vec2> texUVs)
{
    std::vector<hid::Vertex> vertices;

    size_t maxInt = positions.size();
    for (int i = 0; i < maxInt; i++)
    {
        vertices.push_back(
            hid::Vertex{
                positions[i],
                normals[i],
                texUVs[i]});
    }
    return vertices;
}

std::vector<glm::vec2> GLTF::groupFloatsVec2(const std::vector<float> &floatVec)
{
    std::vector<glm::vec2> vectors;
    size_t maxInt = floatVec.size();
    for (int i = 0; i < maxInt; i)
    {
        vectors.push_back(glm::vec2(floatVec[i++], floatVec[i++]));
    }
    return vectors;
}

std::vector<glm::vec3> GLTF::groupFloatsVec3(const std::vector<float> &floatVec)
{
    std::vector<glm::vec3> vectors;
    size_t maxInt = floatVec.size();
    for (int i = 0; i < maxInt; i)
    {
        vectors.push_back(glm::vec3(floatVec[i++], floatVec[i++], floatVec[i++]));
    }
    return vectors;
}

std::vector<glm::vec4> GLTF::groupFloatsVec4(const std::vector<float> &floatVec)
{
    std::vector<glm::vec4> vectors;
    size_t maxInt = floatVec.size();
    for (int i = 0; i < maxInt; i)
    {
        vectors.push_back(glm::vec4(floatVec[i++], floatVec[i++], floatVec[i++], floatVec[i++]));
    }
    return vectors;
}

void GLTF::loadTextures()
{
    static std::string logTag{"hid::GLTF::getTextures"};

    size_t maxInt = JSON["images"].size();
    for (uint32_t i = 0; i < maxInt; i++)
    {

        // uri of current texture
        std::string localTexturePath = JSON["images"][i]["uri"];

        std::string texturePath = fileDirectory + localTexturePath;

        hid::log(logTag, "Image was loaded from " + texturePath);
        hid::Bitmap diffuse = hid::Bitmap{hid::assets::loadBitmap(texturePath)};

        textures.push_back(texturePath);
    }

    //
    // assetManager.loadTextures(textures);
}

void GLTF::traverseNode(const uint32_t &nextNode, const glm::mat4 &matrix)
{
    // Current node
    json node = JSON["nodes"][nextNode];

    // Get translation if it exists
    glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
    if (node.find("translation") != node.end())
    {
        float transValues[3];
        for (uint32_t i = 0; i < node["translation"].size(); i++)
            transValues[i] = (node["translation"][i]);
        translation = glm::make_vec3(transValues);
    }
    // Get quaternion if it exists
    glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    if (node.find("rotation") != node.end())
    {
        float rotValues[4] =
            {
                node["rotation"][3],
                node["rotation"][0],
                node["rotation"][1],
                node["rotation"][2]};
        rotation = glm::make_quat(rotValues);
    }
    // Get scale if it exists
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    if (node.find("scale") != node.end())
    {
        float scaleValues[3];
        for (uint32_t i = 0; i < node["scale"].size(); i++)
            scaleValues[i] = (node["scale"][i]);
        scale = glm::make_vec3(scaleValues);
    }
    // Get matrix if it exists
    glm::mat4 matNode = glm::mat4(1.0f);
    if (node.find("matrix") != node.end())
    {
        float matValues[16];
        for (uint32_t i = 0; i < node["matrix"].size(); i++)
            matValues[i] = (node["matrix"][i]);
        matNode = glm::make_mat4(matValues);
    }

    // Initialize matrices
    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 rot = glm::mat4(1.0f);
    glm::mat4 sca = glm::mat4(1.0f);

    // Multiply all matrices together
    // glm::mat4 matNextNode = matrix * getTransformMatrix();
    glm::mat4 matNextNode = glm::mat4{1.0f};

    // Check if the node contains a mesh and if it does load it
    if (node.find("mesh") != node.end())
    {
        translationsMeshes.push_back(translation);
        rotationsMeshes.push_back(rotation);
        scalesMeshes.push_back(scale);

        matricesMeshes.push_back(matNextNode);

        loadMesh(node["mesh"]);
    }

    // Check if the node has children, and if it does, apply this function to them with the matNextNode
    if (node.find("children") != node.end())
    {
        size_t maxInt = node["children"].size();
        for (uint32_t i = 0; i < maxInt; i++)
            traverseNode(node["children"][i], matNextNode);
    }
}

void GLTF::loadMesh(uint32_t indMesh)
{

    // Get all accessor indices
    uint32_t posAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["POSITION"];
    uint32_t normalAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["NORMAL"];
    uint32_t texAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["TEXCOORD_0"];
    uint32_t indAccInd = JSON["meshes"][indMesh]["primitives"][0]["indices"];

    // Use accessor indices to get all vertices components
    std::vector<float> posVec = getFloats(JSON["accessors"][posAccInd]);
    std::vector<glm::vec3> positions = groupFloatsVec3(posVec);
    std::vector<float> normalVec = getFloats(JSON["accessors"][normalAccInd]);
    std::vector<glm::vec3> normals = groupFloatsVec3(normalVec);
    std::vector<float> texVec = getFloats(JSON["accessors"][texAccInd]);
    std::vector<glm::vec2> texUVs = groupFloatsVec2(texVec);

    // Combine all the vertex components and also get the indices and textures
    std::vector<Vertex> vertices = assembleVertices(positions, normals, texUVs);
    std::vector<uint32_t> indices = getIndices(JSON["accessors"][indAccInd]);
    // std::vector<hid::Bitmap> textures = getTextures();
    meshes.push_back(hid::Mesh{vertices, indices});
}