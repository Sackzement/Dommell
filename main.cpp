
#include <SDL/SDL_platform.h>
//#include "include/myOS.h"
#include "include/Sachen.h"

//myOS os;


#if defined(__WINDOWS__) && defined(_WINDOWS)
int WinMain
#else
int main
#endif

(int argc, char** argv) {

	startGame();

	return 0;// os.start_myOS(argc, argv);
}


