#include "../include/Clonk.h"

#include <Ngin/libs.h>
#include <Ngin/Window.h>
#include <Ngin/TimeManager.h>

namespace clonk {

	int startGame(int argc, char** argv) {

		initLibs();

		Window win;
		win.create();

		

		return 0;
	}

	bool quit = false;
	TimeManager time_man;

	void mainloop() {

		time_man.calcGameAndDeltaTime();
		time_man.resetDelay();

		while ( ! quit ) {
		
			time_man.calcGameAndDeltaTime();
			//scripts
			//input
			//update
			//collision
			time_man.delay();
			//render
		}
	}
}