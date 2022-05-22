#include "../../engine/core/engine.hpp"
#include "../../engine/core/sdl-wrapper.hpp"
// imguiで共有するようのユーザーデータ
#include "../../engine/core/dat.hpp"

#include <functional>
#include <iostream>
#include <memory>

int main(int, char*[])
{
    const std::unique_ptr<hid::Engine> engine = std::make_unique<hid::Engine>();
    engine->init();
    engine->run();
    return 0;
}