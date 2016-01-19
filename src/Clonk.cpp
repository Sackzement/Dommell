#include "../include/Clonk.h"

#include <Ngin/libs.h>
#include <Ngin/Window.h>

namespace clonk {

	int startGame(int argc, char** argv) {

		initLibs();

		Window win;
		win.create();

		

		return 0;
	}


	void mainloop() {

		while (1) {
			pollEvents()
		}
	}
}