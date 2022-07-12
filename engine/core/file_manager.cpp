#include "file_manager.hpp"
#include "../application/application.hpp"

#include "log.hpp"

// #include <cereal/cereal.hpp>
// #include <cereal/types/map.hpp>
// #include <cereal/types/string.hpp>
// #include <cereal/types/vector.hpp>
// #include <cereal/archives/json.hpp>

#include <Windows.h>
#include <shobjidl.h>

using hid::FileManager;

void FileManager::saveScene(const hid::Scene &scene, const std::string &path)
{
    // std::stringstream ss;
    {
        std::ofstream os(path, std::ios::out);
        // cereal::JSONOutputArchive archive(ss);
        cereal::JSONOutputArchive archive(os);
        archive(scene);
    }

    // std::cout << ss.str() << std::endl;
    // #ifdef _MSC_VER
    //             system("pause");
    // #endif
}

void FileManager::openScene(const std::string &path)
{
}

void FileManager::saveFile(const std::string &filter)
{
}
