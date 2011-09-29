#include "OpenGLInstance.h"

#include <iostream>

using namespace std;
using namespace key;

static bool sdl_initialized = false;
static int window_instances = 0;

static bool SDLInit()
{
	if (window_instances == 0)
	{
		/* initialize SDL */
		if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
		{
			cout << "Failed to initialize SDL: " << SDL_GetError() << endl;
			return false;
		} else {
			SDL_EnableUNICODE(true);
			cout << "SDL " << SDL_MAJOR_VERSION << "." << SDL_MINOR_VERSION << "." << SDL_PATCHLEVEL << " initialized." << endl;
		}
		window_instances++;
	} else {
		cout << "Only one SDL window can be running at the same time." << endl;
		return false;
	}
	return true;
}

static void SDLQuit()
{
	if (window_instances == 1)
	{
		SDL_Quit();
	}
	window_instances--;
}

fun_res OpenGLInstance::run() {
	return fun_ok();
}