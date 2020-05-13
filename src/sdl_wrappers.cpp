#include "sdl_wrappers.h"

namespace sdl
{
	System::~System()
	{
		SDL_Quit();
	}

	bool System::Init()
	{
		return SDL_Init(SDL_INIT_VIDEO) >= 0;
	}

	/****************************************************************************************/

	namespace ColorMask
	{
		constexpr uint32_t Red   = 0xFF000000;
		constexpr uint32_t Green = 0x00FF0000;
		constexpr uint32_t Blue  = 0x0000FF00;
		constexpr uint32_t Alpha = 0x000000FF;
	}

	Surface::Surface(SDL_Window* w)
		: surface(SDL_GetWindowSurface(w))
		, windowSurface(true)
	{}

	Surface::Surface(int width, int height)
		: surface(SDL_CreateRGBSurface(0, width, height, 32, ColorMask::Red, ColorMask::Green, ColorMask::Blue, ColorMask::Alpha))
		, windowSurface(false)
	{}

	Surface::~Surface()
	{
		if (!windowSurface) {
			SDL_FreeSurface(surface);
		}
	}

	void Surface::Fill(SDL_Color color)
	{
		auto col = SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a);
		SDL_FillRect(surface, nullptr, col);
	}

	void Surface::SetPixel(int x, int y, SDL_Color color)
	{
		SetPixel(x, y, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
	}

	void Surface::SetPixel(int x, int y, uint32_t color)
	{
		if (surface->format->BitsPerPixel == 32) {
			SetPixel32(x, y, color);
		} else if (surface->format->BitsPerPixel == 24) {
			SetPixel24(x, y, color);
		} else {
			SDL_Rect rect{ x, y, 1, 1 };
			SDL_FillRect(surface, &rect, color);
		}
	}

	void Surface::SetPixel32(int x, int y, uint32_t color)
	{
		auto data = static_cast<uint32_t*>(surface->pixels);
		const auto pitch = surface->pitch / sizeof(uint32_t);
		const size_t idx = pitch * y + x;
		data[idx] = color;
	}

	void Surface::SetPixel24(int x, int y, uint32_t color)
	{
		const uint8_t ch0 = (color & 0x00FF0000) >> 16;
		const uint8_t ch1 = (color & 0x0000FF00) >> 8;
		const uint8_t ch2 = color & 0x000000FF;
		
		auto data = static_cast<uint8_t*>(surface->pixels);
		const size_t idx = surface->pitch * y + x * 3;
		data[idx + 0] = ch0;
		data[idx + 1] = ch1;
		data[idx + 2] = ch2;
	}

	void Surface::SaveToFile(const std::string& filename)
	{
		SDL_SaveBMP(surface, filename.c_str());
	}

	/*****************************************************************************************/

	Window::Window(const char* title, int width, int height)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

		if (window) {
			surface = Surface(window);
		}
	}

	Window::~Window()
	{
		SDL_DestroyWindow(window);
	}

	void Window::Update()
	{
		SDL_UpdateWindowSurface(window);
	}


	
}