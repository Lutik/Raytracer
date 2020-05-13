#pragma once

#include <SDL.h>

#include <string>

namespace sdl
{
	#define MOVABLE_NONCOPYABLE(className) \
		className(const className&) = delete; \
		className& operator=(const className&) = delete; \
		className(className&&) = default; \
		className& operator=(className&&) = default;

	struct System
	{
		System() = default;
		~System();

		bool Init();
	};

	class Surface
	{
	public:
		Surface() = default;
		Surface(int width, int height);
		explicit Surface(SDL_Window* w);
		~Surface();

		MOVABLE_NONCOPYABLE(Surface)

		operator bool() const { return surface != nullptr; }

		int Width() const { return surface->w; }
		int Height() const { return surface->h; }

		void Fill(SDL_Color color);
		void SetPixel(int x, int y, SDL_Color color);
		void SetPixel(int x, int y, uint32_t color);

		void SaveToFile(const std::string& filename);

	public:
		SDL_Surface* surface = nullptr;
		bool windowSurface = false;

	private:
		void SetPixel32(int x, int y, uint32_t color);
		void SetPixel24(int x, int y, uint32_t color);
	};

	struct Window
	{
		Window(const char* title, int width, int height);
		~Window();

		MOVABLE_NONCOPYABLE(Window)

		operator bool() const { return window != nullptr; }

		void Update();

		SDL_Window* window = nullptr;
		Surface surface;
	};
}
