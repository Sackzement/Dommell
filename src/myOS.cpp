#include "../include/myOS.h"






#include <Ngin/libs.h>
#include <Ngin/window.h>
#include <SDL2/SDL_rwops.h>
#include <string>
#include <vector>
using std::string;
using std::vector;

const char * save_file_name = "settings.save";


char* copy_to_mem(SDL_RWops *file);





int start_myOS(int argc, char** argv) {
    
    initLibs();
    Window win;
    
    if (SDL_RWops *save_file = SDL_RWFromFile(save_file_name,"rb"))// check  if there is a save file
    {
        // if YES
        {
            char *file_content = copy_to_mem(save_file);
            
            vector<string> words;
            vector<Uint8> types;
            //separate words in file (by spaces/new_line) till end of file
            
            // analyse tags and values
            //interpret
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











