#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_video.h>

SDL_Window* sdl_window;
SDL_Renderer* sdl_renderer;
bool running = true;

struct vec2d {
	double x,y;
	vec2d(double xx=0., double yy=0.) : x(xx), y(yy) {}
};
struct Transform {
	vec2d pos, size;
	Transform(double xx = 0., double yy = 0., double ww = 1., double hh = 1.) : pos(xx,yy),size(ww,hh) {}
	Transform& operator<<(const Transform& rhs) {
		this->pos.x  += this->size.x * rhs.pos.x;
		this->pos.y  += this->size.y * rhs.pos.y;
		this->size.x *= rhs.size.x;
		this->size.y *= rhs.size.y;
		return *this;
	}
};

struct RenderComponent : public Transform {

	virtual void render(Transform offset = Transform()) = 0;
};
struct Shape : public RenderComponent {
	SDL_Color color;
	Shape() : color({255,255,255,255}) {}
};
struct Rect : public Shape{
	void render(Transform offset = Transform()) {

		offset << *this;
		SDL_Rect rect = { offset.pos.x,offset.pos.y,offset.size.x,offset.size.y };
		
		SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawRect(sdl_renderer, &rect);
	}
};
struct RenderObject : public RenderComponent {

	vector<RenderObject*> child_renderobjs;
};
struct Object : public RenderObject {

	vector<Object*> childobjs;
};





#include <vector>
#include <map>
#include <functional>
using std::vector;
using std::map;
using std::function;

struct InputManager {

	struct {
		int x, y;
		Uint32 state;
	}mouse;
	struct {
		const Uint8* state;
		int numkeys;
	}keyboard;

	function<void()> mousedownevent;
	map <SDL_Scancode,function<void()>> keydownevents;

	void init() {
		keyboard.state = SDL_GetKeyboardState(&keyboard.numkeys);
	}

	void process() {

		mouse.state = SDL_GetMouseState(&mouse.x, &mouse.y);

		SDL_Event ev;
		while (SDL_PollEvent(&ev))
			switch (ev.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				try
				{
					function<void()> func = keydownevents.at(ev.key.keysym.scancode);
					func();
				}
				catch (const std::out_of_range&) {}
				break;
			case SDL_MOUSEBUTTONDOWN:
				mousedownevent();
				break;
			}
		
	}

} input_manager;

struct RenderManager {

	vector<function<void(Transform)>> renderfuncs;

	void process() {
		SDL_SetRenderTarget(sdl_renderer, nullptr);
		SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
		SDL_RenderClear(sdl_renderer);

		const size_t num_of_objs = renderfuncs.size();
		for (size_t i = 0; i < num_of_objs; ++i)
			renderfuncs[i] ( Transform(0., 0., 120., 120.) );

		SDL_RenderPresent(sdl_renderer);
	}
}render_manager;


//GOmanager scene;



struct GO {

};


void openWindow() {
		
	if (!SDL_WasInit(SDL_INIT_VIDEO))
		SDL_Init(SDL_INIT_VIDEO);

	if (!sdl_window)
		sdl_window = SDL_CreateWindow("Sachen", 0, 0, 1920, 1080, SDL_WINDOW_BORDERLESS);

	//if (sdl_window)
	//	SDL_ShowWindow(sdl_window);

	if (!sdl_renderer) {
		sdl_renderer = SDL_GetRenderer(sdl_window);
	if (!sdl_renderer)
		sdl_renderer = SDL_CreateRenderer(sdl_window, -1, 10);
	}

}






void mainloop() {
	while (running)
	{
		SDL_Delay(1000 / 60);
		input_manager.process();
		render_manager.process();
	}
	
}

void startGame() {
	openWindow();
	

	render_manager.renderfuncs.push_back(new Rect());

	input_manager.init();
	input_manager.keydownevents[SDL_SCANCODE_Q] = []() {running = false; };
	input_manager.mousedownevent = []() {
		Rect* r = new Rect();
		r->pos.x = double(input_manager.mouse.x) / 120.;
		r->pos.y = double(input_manager.mouse.y) / 120.;
		render_manager.renderfuncs.push_back(r); };
	
	mainloop();
}