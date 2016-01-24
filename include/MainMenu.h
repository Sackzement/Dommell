#pragma once

#include <SDL/SDL_render.h>



class MainMenu {

	SDL_Texture * background;
	struct 
	{
		SDL_Texture * texture;
		struct 
		{
			double x, y;
		}position;
		struct
		{
			double x, y;
		}size;
	}button;

public:
void alloc();
void render(SDL_Renderer * ren)

}