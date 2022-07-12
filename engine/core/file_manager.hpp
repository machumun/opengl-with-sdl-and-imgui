#pragma once

#include "scene/scene.hpp"

#include <fstream>
#include <iostream>
#include <string>

namespace hid
{
    struct FileManager
    {
        FileManager() = default;
        ~FileManager() = default;

        void saveScene(const hid::Scene &scene, const std::string &path);

        void openScene(const std::string &path);

        // bool openFile(std::string *sSelectedFile, std::string *sFilePath);
        // void runOpenProcess();
        void saveFile(const std::string &filter);

        void importAsset() {}

        void buildGame() {}
    };
}