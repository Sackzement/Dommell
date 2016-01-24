
#include <SDL/SDL_platform.h>
#include "include/myOS.h"

myOS os;


#if defined(__WINDOWS__) && defined(_WINDOWS)
int WinMain
#else
int main
#endif

(int argc, char** argv) {

    return os.start_myOS(argc,argv);
}


