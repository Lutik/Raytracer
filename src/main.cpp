
#include "sdl_wrappers.h"

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

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

        window.surface.Fill({ 120, 200, 200, 255 });
        window.Update();
    }

    return 0;
}