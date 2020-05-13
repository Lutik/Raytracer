
#include "sdl_wrappers.h"

#include "RT/Raytracer.h"
#include <algorithm>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr auto SCREEN_RECT = RT::Rect{ 0, 0, WIDTH, HEIGHT };
constexpr float ASPECT = static_cast<float>(WIDTH) / HEIGHT;

namespace RT
{
    const Scene TestScene = {
        { Sphere{ {6.0f, 0.5f, 0.0f}, 0.3f }, MtDiffuse{ Color{0.0f, 0.8f, 0.8f} } },
        { Sphere{ {6.0f, -0.5f, 0.0f}, 0.4f }, MtLight{} }
    };

    const Camera TestCamera{
        {0, 0, 0},
        {1, 0, 0},
        {0, 0, 1},
        RT::deg2rad(45.0f),
        ASPECT
    };
}



constexpr SDL_Color LightToSDL(RT::Light color) {
    auto r = static_cast<uint8_t>(std::clamp(color.x, 0.0f, 1.0f) * 255.0f);
    auto g = static_cast<uint8_t>(std::clamp(color.y, 0.0f, 1.0f) * 255.0f);
    auto b = static_cast<uint8_t>(std::clamp(color.z, 0.0f, 1.0f) * 255.0f);
    return SDL_Color{ r, g, b, 255 };
}

void BlitToTarget(const RT::LightMap& lightMap, float exposition, sdl::Surface& target)
{
    const int width = target.Width();
    const int height = target.Height();

    const auto area = lightMap.GetRect();

    for (int y = area.y; y < area.y + area.height; ++y) {
        for (int x = area.x; x < area.x + area.width; ++x) {
            auto col = lightMap[{x, y}] / exposition;
            target.SetPixel(x, y, LightToSDL(col));
        }
    }
}

int main(int argc, char* args[])
{
    // Init SDL
    sdl::System sdlSystem;
    if (!sdlSystem.Init())
        return 0;

    //Create window
    sdl::Window window{ "Raytracer", WIDTH, HEIGHT };
    if (!window)
        return 0;

    const auto lightMap = RT::Render(RT::TestScene, RT::TestCamera, SCREEN_RECT);

    BlitToTarget(lightMap, 0.25f, window.surface);

    bool quit = false;
    while (!quit)
    {
        //Handle events on queue
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        window.Update();
    }

    return 0;
}