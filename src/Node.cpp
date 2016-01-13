

#include "../include/Node.h"

#include <Ngin/Ngin.h>
#include <Ngin/libs.h>
#include <Ngin/window.h>
#include <Ngin/renderer.h>
#include <Ngin/textures.h>
#include <SDL/SDL_log.h>

namespace node {
/*class Controls : public Object
{
	void input() override
	{
		if (ngin.isKeyDownOnce(ngin.controls.back))
			ngin.quit();


		if (ngin.isKeyDownOnce(SDL_SCANCODE_S))
			SDL_SetWindowFullscreen(ngin.getWindow(), 0);

		if (ngin.isKeyDownOnce(SDL_SCANCODE_F))
			SDL_SetWindowFullscreen(ngin.getWindow(), SDL_WINDOW_FULLSCREEN);

		if (ngin.isKeyDownOnce(SDL_SCANCODE_D))
			SDL_SetWindowFullscreen(ngin.getWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP);


		if (ngin.isKeyDownOnce(SDL_SCANCODE_C))
		{
			Rect* rect = new Rect();
			rect->color = { 255,0,0,255 };
			rect->size.x = 200;
			rect->size.y = 200;
			ngin.addObject(rect);
		}

	}
};*/


	/*
int startGame(int argc, char** argv)
{
	initLibs();
    Window::create();
    Renderer::create();
	

    Window::setFullscreen();

	//Controls* ctrl = new Controls();
	//ngin.addObject(ctrl);
	textures.loadTexture("res/cat.png");
	textures.loadTexture("res/aaa.png");

	
	for (auto it = textures.list.begin(); it != textures.list.end(); ++it)
		SDL_Log("%s ->  %s  %i %i  %x", (*it).first, (*it).second.name, (*it).second.width, (*it).second.height, (*it).second.texturePtr);
	ngin.enterMainLoop();

	getchar();
	
    Window::destroy();
    Renderer::destroy();
	quitLibs();
	
	getchar();

	return 0;
}*/
}
