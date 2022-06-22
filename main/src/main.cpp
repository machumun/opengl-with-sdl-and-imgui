#include "../../engine/core/engine.hpp"
#include "../../engine/core/wrapper/sdl_wrapper.hpp"

#include <functional>
#include <iostream>
#include <memory>

int main(int, char*[])
{
    const std::unique_ptr<hid::Engine> engine = std::make_unique<hid::Engine>();
    engine->setup();
    engine->run();
    return 0;
}