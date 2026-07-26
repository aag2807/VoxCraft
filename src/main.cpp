#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <spdlog/spdlog.h>
#include "core/Window.h"
#include "core/Engine.h"

int main(int argc, char* argv[])
{
    spdlog::set_level(spdlog::level::debug);

    Window window("Voxel Craft", 1280, 720);
    if (!window.init())
    {
        spdlog::error("Failed to initialize window");
        return 1;
    }

    Engine engine(window);
    engine.run();

    return 0;
}
