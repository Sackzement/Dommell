#include "../include/myOS.h"


#include "../include/Settings.h"



#include <Ngin/libs.h>
#include <Ngin/window.h>
#include <Ngin/TimeManager.h>
#include <SDL/SDL_rwops.h>
#include <string>
#include <vector>
using std::string;
using std::vector;
#include <cctype>



Window win;
bool quit = false;
TimeManager time_man;




char* copy_to_mem(SDL_RWops *file);


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


vector<string> * create_vector_of_strings(const char * const str);
vector<word> * create_vector_of_words_with_types(const vector<string> & const cmnds);
void interpret(const vector<word> & words);






bool createWin() {

	// load last window settings from file  if possible   (flags should not create hidden/minimized window)

	//create window
	win.create(window_title,
		default_settings.win_x, 
		default_settings.win_y, 
		default_settings.win_w, 
		default_settings.win_h, 
		default_settings.win_flag);

	return true;
}

int start_mainloop() {

	while (!quit) {
		time_man.calcGameAndDeltaTime();
		//doScripts
	}

	return 0;
}

// MAIN ENTRYPOINT
int start_myOS(int argc, char** argv) {

	initLibs();

	createWin();
    
    return start_mainloop();
}








bool loadSettingsFromSaveFile() {

	if (SDL_RWops * save_file = SDL_RWFromFile(save_file_name, "rb"))// check  if there is a save file
	{
		// if YES
		{

			char * file_content = copy_to_mem(save_file);
			SDL_RWclose(save_file);

			vector<string> * words = create_vector_of_strings(file_content);
			free(file_content);

			vector<word> * types = create_vector_of_words_with_types(*words);

			//interpret
			{
				if (words->size() >= 4) {
					int i = 0;
					if ((*words)[i].compare("win") == 0)
						if ((*words)[++i].compare("res") == 0); i++;
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
}







vector<word> * create_vector_of_words_with_types(const vector<string>  & const words) {
    
    
    vector<word> * words_w_types = new vector<word>();
    
	int numWords = words.size();
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



