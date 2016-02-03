#pragma once

#include <SDL/SDL_video.h>
#include <SDL/SDL_render.h>

struct Game {

	bool			running = true;

	SDL_Window*		sdl_window;
	SDL_Renderer*	sdl_renderer;

	void start() {

	}
}game;