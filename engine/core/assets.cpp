#define TINYOBJLOADER_IMPLEMENTATION

#include "assets.hpp"
#include "sdl-wrapper.hpp"
#include "vertex.hpp"
#include "log.hpp"

#include <SDL_image.h>
#include <tiny_obj_loader.h>

#include <sstream>
#include <unordered_map>
#include <vector>

#include "json.hpp"

using nlohmann::json;

std::string hid::assets::loadTextFile(const std::string &path)
{
    // Open a file operation handle to the asset file.
    SDL_RWops *file{SDL_RWFromFile(path.c_str(), "r")};

    // Determine how big the file is.
    size_t fileLength{static_cast<size_t>(SDL_RWsize(file))};

    // Ask SDL to load the content of the file into a data pointer.
    void *data{SDL_LoadFile_RW(file, nullptr, 1)};

    // Construct a new string based on the data pointer.
    std::string result(static_cast<char *>(data), fileLength);

    // Free up the original SDL managed data pointer.
    SDL_free(data);

    // Hand back the resulting string which is the content of the file.
    return result;
}

hid::Mesh hid::assets::loadOBJFile(const std::string &path)
{

    std::istringstream sourceStream(hid::assets::loadTextFile(path));

    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warning;
    std::string error;

    if (!tinyobj::LoadObj(
            &attributes,
            &shapes,
            &materials,
            &warning,
            &error,
            &sourceStream))
    {
        throw std::runtime_error("hid::assets::loadOBJFile: Error: " + warning + error);
    }

    std::vector<hid::Vertex> vertices;
    std::vector<uint32_t> indices;
    std::unordered_map<hid::Vertex, uint32_t> uniqueVertices;

    for (const auto &shape : shapes)
    {

        for (const auto &index : shape.mesh.indices)
        {
            glm::vec3 position{
                attributes.vertices[3 * index.vertex_index + 0],
                attributes.vertices[3 * index.vertex_index + 1],
                attributes.vertices[3 * index.vertex_index + 2]};

            glm::vec2 texCoord{
                attributes.texcoords[2 * index.texcoord_index + 0],
                1.0f - attributes.texcoords[2 * index.texcoord_index + 1]};

            glm::vec3 normal{
                attributes.normals[3 * index.normal_index + 0],
                attributes.normals[3 * index.normal_index + 1],
                attributes.normals[3 * index.normal_index + 2]};

            hid::Vertex vertex{position, normal, texCoord};

            {
                uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                vertices.push_back(vertex);
            }

            indices.push_back(uniqueVertices[vertex]);
        }
    }

    return hid::Mesh{vertices, indices};
}

hid::Bitmap hid::assets::loadBitmap(const std::string &path)
{
    SDL_RWops *file{SDL_RWFromFile(path.c_str(), "rb")};
    SDL_Surface *source{IMG_Load_RW(file, 1)};
    SDL_Rect imageFrame{0, 0, source->w, source->h};

    uint32_t redMask;
    uint32_t greenMask;
    uint32_t blueMask;
    uint32_t alphaMask;

#if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
    redMask = 0xff000000;
    greenMask = 0x00ff0000;
    blueMask = 0x0000ff00;
    alphaMask = 0x000000ff;
#else
    redMask = 0x000000ff;
    greenMask = 0x0000ff00;
    blueMask = 0x00ff0000;
    alphaMask = 0xff000000;
#endif

    SDL_Surface *target{SDL_CreateRGBSurface(
        0,
        imageFrame.w, imageFrame.h,
        32,
        redMask, greenMask, blueMask, alphaMask)};

    SDL_BlitSurface(source, &imageFrame, target, &imageFrame);

    SDL_FreeSurface(source);

    return hid::Bitmap(target);
}

hid::GLTF loadGLTF(const std::string &path)
{

    static const std::string logTag{"hid::assets::loadGLTF"};

    hid::GLTF gltf;

    // make json object
    std::string sourceStream(hid::assets::loadTextFile(path));
    gltf.JSON = json::parse(sourceStream);

    std::string bytesText;
    std::string uri = gltf.JSON["buffers"][0]["uri"];
    std::string fileDirectory = sourceStream.substr(0, sourceStream.find_last_of('/') + 1);
    bytesText = hid::assets::loadTextFile((fileDirectory + uri).c_str());
    std::vector<unsigned char> data(bytesText.begin(), bytesText.end());

    gltf.data = data;

    gltf.traverseNode(0);

    return gltf;
}
