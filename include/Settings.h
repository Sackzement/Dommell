#pragma once
#include <vector>
#include <string>
using std::vector;
using std::string;





struct Settings
{
	int win_x,
		win_y,
		win_w,
		win_h,
		win_flags,
		ren_driverIdx,
		ren_flags;

	Settings() {}
	Settings(int wx,int wy,int ww,int wh,int wf,int ri,int rf) :
		win_x(wx),
		win_y(wy),
		win_w(ww),
		win_h(wh),
		win_flags(wf),
		ren_driverIdx(ri),
		ren_flags(rf)
	{}

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
	vector<string> * create_vector_of_strings(char * str) {

		vector<string> * words = new vector<string>();

		int i = 0;
		string word_buf = "";
		while (1) {
			char c = str[i];

			if (isalnum(c)) {
				word_buf += c;
			}
			else if (isspace(c)) {
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
	}


	bool loadFromFile(const char*const filepath) {
		// open file
		if (SDL_RWops * save_file = SDL_RWFromFile(filepath, "rb")) {

			// load file content into main mem  
			char * file_content = copy_to_mem(save_file);
			SDL_RWclose(save_file);

			// put into vector<string> seperated by blank chars
			vector<string> * words = create_vector_of_strings(file_content);
			free(file_content);

			// search for:
			// window		// winx XXX
			// winy XXX
			// ...
			// decide what to do with values if some are missing

			return true;
		}
	}
	bool saveToFile() {
		//
        return true;
	}
};














