#pragma once

char const * const window_title = "myOS";
const char * save_file_name = "settings.save";

struct Settings
{
	int win_x,
		win_y,
		win_w,
		win_h,
		win_flag;

	Settings() {}
	Settings(int wx, int wy, int ww, int wh, int wf) :
		win_x(wx),
		win_y(wy),
		win_w(ww),
		win_h(wh),
		win_flag(wf)
	{}

	bool loadFromFile(const char*const filepath) {
		// check if file exists
		// open file
		// load file content into main mem  
		// put into vector<string> seperated by blank chars
		// search for:
		// window
		// winx XXX
		// winy XXX
		// ...
		// decide what to do with values if some are missing
	}
	bool saveToFile() {
		//
	}
};



const Settings default_settings(100,100,1280,720,4);











