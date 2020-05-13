
#include "sdl_wrappers.h"

#include "RT/Raytracer.h"
#include <algorithm>
#include <future>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr auto SCREEN_RECT = RT::Rect{ 0, 0, WIDTH, HEIGHT };
constexpr float ASPECT = static_cast<float>(WIDTH) / HEIGHT;

namespace RT
{
    const Scene TestScene = {
        { Plane{ {7.0f, 0.0f, 0.0f}, -UnitVecX }, MtDiffuse{ Color{0.0f, 0.8f, 0.8f} } },
        { Plane{ {7.0f, 0.0f, 0.5f}, {-0.3f, 0.0f, -0.7f} }, MtMirror{} },
        { Sphere{ {6.5f, 0.0f, 0.0f}, 0.3f }, MtDiffuse{ Color{1.0f, 0.8f, 0.0f} } },
        { Sphere{ {6.0f, -0.7f, 0.0f}, 0.3f }, MtLight{} }
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



std::vector<std::future<RT::LightMap>> GenerateRenderTasks(const RT::Scene& scene, const RT::Camera& camera, const RT::Rect& screenRect, int threads)
{
    std::vector<std::future<RT::LightMap>> tasks;

    const int areaHeight = screenRect.height / threads;
    for (int i = 0; i < threads; ++i) {
        const RT::Rect area{ 0, i * areaHeight, WIDTH, areaHeight };
        tasks.push_back(std::async(std::launch::async, RT::Render, scene, camera, screenRect, area));
    }

    return tasks;
}

std::vector<RT::LightMap> UpdateTasks(std::vector<std::future<RT::LightMap>>& tasks)
{
    // move finished tasks to end
    auto is_running = [](const auto& task) {
        return !task.valid() || task.wait_for(std::chrono::seconds(0)) != std::future_status::ready;
    };
    auto ready_itr = std::partition(tasks.begin(), tasks.end(), is_running);

    // retrieve results
    std::vector<RT::LightMap> results;
    auto get_result = [](auto& task) { return task.get(); };
    std::transform(ready_itr, tasks.end(), std::back_inserter(results), get_result);

    // erase finished tasks
    tasks.erase(ready_itr, tasks.end());

    return results;
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

    auto threads = GenerateRenderTasks(RT::TestScene, RT::TestCamera, SCREEN_RECT, 8);
    sdl::Surface target{ WIDTH, HEIGHT };
    RT::LightMap lightMap{ SCREEN_RECT, RT::NoLight };

    bool quit = false;
    while (!quit)
    {
        //Handle events on queue
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            if (threads.empty())
            {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }
        }

        const auto results = UpdateTasks(threads);
        if (!results.empty())
        {
            for (const auto& fragment : results) {
                RT::CopyArray2DData(fragment, lightMap);
            }
            const float exposition = 0.25f;
            BlitToTarget(lightMap, exposition, window.surface);
            window.Update();
        }
    }

    return 0;
}