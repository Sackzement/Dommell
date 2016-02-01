#include "../include/myOS.h"





#include <Ngin/libs.h>
//#include <Ngin/window.h>
#include <Ngin/HardwareInfo.h>
#include <SDL/SDL_rwops.h>
#include <SDL/SDL_events.h>
#include <string>
#include <vector>
//using std::string;
using std::vector;
#include <cctype>
#include <Ngin/Log.h>









//char* copy_to_mem(SDL_RWops *file);


enum struct word_type : Sint8 {
	undef = -1,
	tag = 0,
	num = 1,
};

enum struct tag_type : Sint8 {
	undef = -1,
	win = 0,
	res = 1,
};

struct tag {
	word_type type = word_type::tag;
	tag_type val = tag_type::undef;
};
struct num {
	word_type type = word_type::num;
	Sint64 val = 0;
};
union word {
	word_type type = word_type::undef;
	tag tag;
	num num;
};


//vector<string> * create_vector_of_strings(const char * const str);
//vector<word> * create_vector_of_words_with_types(vector<string> & cmnds);
//void interpret(const vector<word> & words);






void myOS::createWin() {

	// load last window settings from file  if possible   (flags should not create hidden/minimized window)

	//create window
	window = SDL_CreateWindow("myOS",
		default_settings.win_x,
		default_settings.win_y,
		default_settings.win_w,
		default_settings.win_h,
		default_settings.win_flags);

}

void myOS::createRenderer() {
	renderer = SDL_CreateRenderer(window,
		default_settings.ren_driverIdx,
		default_settings.ren_flags);
}


void separate(vector<uint> &into, uint num) {

	if (num == 0)
		into.push_back(0);
	else
		into.push_back(1);

	while (num % 2 == 0) {
		into.push_back(2);
		num /= 2;
	}
	uint halfnum = num / 2;
	for (uint i = 3; i <= halfnum; ++i, ++i)
		while (num % i == 0) {

			into.push_back(i);
			num /= i;
		}
}

uint calcBiggestMulti(uint x, uint y) {

	vector<uint> xParts; separate(xParts, x);
	vector<uint> yParts; separate(yParts, y);
	//break x down
	vector<uint> xunter;
	{
		uint tempX = x;

		for (uint i = 2; i <= x / 2; ++i)
			while (tempX % i == 0) {
				xunter.push_back(i);
				std::printf(" %i", i);
				tempX /= i;
			}
	}

	// break y down
	vector<uint> yunter;
	{
		uint tempY = y;
		std::printf("   ");
		for (uint i = 2; i <= y / 2; ++i)
			while (tempY % i == 0) {
				yunter.push_back(i);
				std::printf(" %i", i);
				tempY /= i;
			}

		std::printf("\n");
	}

	const uint sX = (uint)xunter.size();
	const uint sY = (uint)yunter.size();
	if (sX > 0 && sY > 0) {
		vector<uint> gem;
		uint iX = 0;
		uint iY = 0;

		// store same values in gem
		for (; iX < sX && iY < sY;) {
			uint xx = xunter[iX];
			uint yy = yunter[iY];
			if (xx == yy) {
				gem.push_back(xx);
				++iX; ++iY;
			}
			else if (xx < yy)
				++iX;
			else
				++iY;
		}

		// multiply gem values
		uint mul = 1;

		for (uint i = 0; i < gem.size(); ++i) {
			mul *= gem[i];
			std::printf(" %u", gem[i]);
		}
		std::printf("\n");
		return mul;
	}

	return 0;
}

HardwareInfo getHardwareInfo() {
	// 2715 1527
	// 905 509  fac(3)
	int resx, resy, aspx, aspy, fac;
	resx = 1920;
	resy = 1080;
	fac = calcBiggestMulti(resx,resy);
	aspx = resx / fac;
	aspy = resy / fac;



	HardwareInfo info;

	info.update();

	return info;
}

void myOS::testGPUram() {
	static Uint64 all = 0;

	for (int i = 1;; ++i) {
		Uint64 num = pow(2, i);
		Uint64 num2 = sqrt(num);
		SDL_Texture* tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, num2, num2);
		
		if (tex) {
			all += num2 * num2;
		}
		else {
			Log(std::string() + "\n" + SDL_GetError() + "\nTexture RAM allocated :  " + std::to_string(all));
			break;
		}

	}

}
void myOS::createBG() {
	bg = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1920, 1080);
	if (!bg)
		Log(string() + "\n" + SDL_GetError());
	else {
		SDL_SetRenderTarget(renderer, bg);

		for (int iy = 0; iy < 1080; ++iy) {
			Uint8 col =(255./1079.) * (double)iy;
			SDL_SetRenderDrawColor(renderer, col,col,col,255);
			for (int ix = 0; ix < 1920; ++ix)
				SDL_RenderDrawPoint(renderer, ix, iy);
		}
	}
}
#include <SDL/SDL_image.h>
void myOS::loadResources() {

	const char * respath = "../res/bg.png";
	SDL_Surface* surf = IMG_Load(respath);

	if (!surf) {

		Log(string() + "\n" + SDL_GetError());
	}
	else {
		bg = SDL_CreateTextureFromSurface(renderer, surf);
		if (!bg)
			Log(string() + "\nError:  Failed to create Texture from Surface image  " + respath + "  " + SDL_GetError());

		SDL_FreeSurface(surf);
	}
}
void myOS::exeScriptList() {

	int size = scriptList.size();
	
	for (int i = 0; i < size; ++i)
		scriptList[i]();

	scriptList.clear();

}
void myOS::input() {

	keyboard.reset_onces();

	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {

		switch (ev.type) {

			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				if (ev.key.repeat == 0)
					keyboard.input_keydown(ev.key.keysym.scancode);
				break;
			case SDL_KEYUP:
				keyboard.input_keyup(ev.key.keysym.scancode);
				break;
		}
	}

	// MAIN INPUT


	if (keyboard.down_once[SDL_SCANCODE_Q] ||
		keyboard.down_once[SDL_SCANCODE_ESCAPE])
		quit = true;
	if (keyboard.down_once[SDL_SCANCODE_D])
		SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);
	if (keyboard.down_once[SDL_SCANCODE_F])
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	if (keyboard.down_once[SDL_SCANCODE_G])
		SDL_SetWindowFullscreen(window, 0);
	if (keyboard.down_once[SDL_SCANCODE_H]) {
		SDL_SetWindowFullscreen(window, 0);
		SDL_SetWindowBordered(window, SDL_FALSE);
		SDL_SetWindowPosition(window, 1920, 0);
		SDL_SetWindowSize(window, 1920, 1080);
	}
	if (keyboard.down_once[SDL_SCANCODE_M])
		SDL_SetWindowGrab(window, SDL_TRUE);
	if (keyboard.down_once[SDL_SCANCODE_N])
		SDL_SetWindowGrab(window, SDL_FALSE);
	
	/*for (auto it = m_objects.begin(); it != m_objects.end(); ++it) {

		(*it).input();
	}*/
}
void myOS::update() {

}
void myOS::render() {
	
	SDL_SetRenderTarget(renderer,nullptr);
	SDL_SetRenderDrawColor(renderer,0,0,0,0);
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, bg, nullptr, nullptr);
	// mainmenu.render();
	SDL_RenderPresent(renderer);
}
void myOS::start_mainloop() {

	time.resetDelay();

	while (!quit) {

		time.update();
		exeScriptList();
		input();
		update();
		render();
		time.delay();
	}

}
//====================================================================
// MAIN ENTRYPOINT
//====================================================================

int myOS::start_myOS(int argc, char** argv) {

	initLibs();

	getHardwareInfo();

	createWin();

	createRenderer();

	//loadResources();
	//testGPUram();
	//createBG();
	//switchToScene(Scene);

	start_mainloop();
    
	return 0;
}








/*
bool loadSettingsFromSaveFile() {

	if (SDL_RWops * save_file = SDL_RWFromFile(save_file_name, "rb"))// check  if there is a save file
	{
		// if YES
		{

			char * file_content = copy_to_mem(save_file);
			SDL_RWclose(save_file);

			vector<string> * words = create_vector_of_strings(file_content);
			free(file_content);

			//vector<word> * types = create_vector_of_words_with_types(*words);

			//interpret
			{
				if (words->size() >= 4) {
					int i = 0;
					if ((*words)[i].compare("win") == 0)
                        if ((*words)[++i].compare("res") == 0) {}
							//if ((*types)[++i] == word_type::num
								//&& (*types)[++i] == word_type::num) {

							//win_w = std::stoi((*words)[--i]);
				}


				
			}
		}

		// create window with last saved values
	}
	return true;
}
*/
/*
char* copy_to_mem(SDL_RWops *file) {
    
    Sint64 res_size = SDL_RWsize(file);
    char* res = (char*)malloc(res_size + 1);
    
    Sint64 nb_read_total = 0, nb_read = 1;
    char* buf = res;
    while (nb_read_total < res_size && nb_read != 0) {
        nb_read = SDL_RWread(file, buf, 1, (res_size - nb_read_total));
        nb_read_total += nb_read;
        buf += nb_read;
    }
    if (nb_read_total != res_size) {
        free(res);
        return NULL;
    }
    
    res[nb_read_total] = '\0';
    return res;
}






vector<string> * create_vector_of_strings(const char * const str) {
    
    vector<string> * words = new vector<string>();
    
    int i = 0;
    string word_buf = "";
    while (1) {
        char c = str[i];
        
        if ( isalnum(c) ) {
            word_buf += c;
        }
        else if ( isspace(c) ) {
            if (word_buf.size() > 0) {
                words->push_back(word_buf);
                word_buf.clear();
            }
        }
        else if (c == '\0') {
            if (word_buf.size() > 0) {
                words->push_back(word_buf);
                word_buf.clear();
            }
            break;
        }
        else {
            word_buf += c;
        }
        
        ++i;
    }
    
    
    return words;
}*/






/*
vector<word> * create_vector_of_words_with_types(const vector<const string>  & words) {
    
    
    vector<word> * words_w_types = new vector<word>();
    
	int numWords = (int)words.size();
	for (int i = 0; i < numWords; ++i) {
		char firstChar = words[i][0];

		if (isalpha(firstChar)) {
			//word w;
			//w.type = word_type::tag;
			//w.tag.val = std::stoi(words[i]);
			//words_w_types->push_back(word_type::tag);
		}
		else if (isdigit(firstChar)) {
			//words_w_types->push_back(word_type::num);
		}
	}
    
    
    
    return words_w_types;
}

*/

