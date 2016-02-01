#pragma once
#include <Ngin/TimeManager.h>
#include <SDL/SDL_video.h>
#include <SDL/SDL_render.h>
#include <Ngin/Keyboard.h>
#include "../include/Settings.h"
#include <functional>

struct myOS
{
	int start_myOS(int argc, char** argv);

private:
	Time time;
	SDL_Window* window;
	SDL_Renderer* renderer;

	bool quit = false;
	std::vector<std::function<void()>>  scriptList;
	std::vector<std::function<void()>>  inputList;
	Keyboard keyboard;

	SDL_Texture* bg;


	const Settings default_settings = Settings(1920, 0, 1920, 1080, SDL_WINDOW_BORDERLESS, -1, 10);




	void createWin();
	void createRenderer();

	void testGPUram();
	void createBG();
	void loadResources();

	void exeScriptList();
	void input();
	void update();
	void render();
	
	void start_mainloop();

};




