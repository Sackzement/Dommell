#include "../include/myOS.h"






#include <Ngin/libs.h>
#include <Ngin/window.h>
#include <SDL2/SDL_rwops.h>
#include <string>
#include <vector>
using std::string;
using std::vector;
#include <cctype>

const char * save_file_name = "settings.save";


char* copy_to_mem(SDL_RWops *file);



vector<string> * create_vector_of_words(const char* str);
vector<Uint8> * create_vector_of_types(const vector<string> * const words);







int start_myOS(int argc, char** argv) {
    
    initLibs();
    Window win;
    
    // SAVE FILE ACTION
    if (SDL_RWops * save_file = SDL_RWFromFile(save_file_name,"rb"))// check  if there is a save file
    {
        // if YES
        {
            
            char * file_content = copy_to_mem(save_file);
            SDL_RWclose(save_file);
            
            vector<string> * words = create_vector_of_words(file_content);
            free(file_content);
            
            //
            vector<Uint8> * types = create_vector_of_types(words);
            
            //interpret
            {
                int num_of_words = (int)words->size();
                for(int i=0; i < num_of_words; ++i) {
                    if ( (*words)[i].compare("window" == 0 )
                }
            }
        }
        
        // create window with last saved values
    }
    else
    {
        // if NO
        // create window with standard values
        // save values into save file
        
    }
    
    
    {
        int desktop_width_two_third, desktop_height_two_third;
        
        win.create("myOS", 100,100, 951,540);
        
    }
    
    return 0;
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






vector<string> * create_vector_of_words(const char* str) {
    
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






vector<Uint8> * create_vector_of_types(const vector<string> * const words) {
    
    if ( ! words )    return nullptr;
    
    vector<Uint8> * types = new vector<Uint8>();
    
    
    
    
    
    return types;
}



