#include "Window.h"

#include <iostream>
#include <SDL.h>

using namespace std;
namespace cv = cvv8;
using namespace v8;

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
	}
	window_instances++;
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

namespace cvv8 {
    CVV8_TypeName_IMPL((key::Window),"Window");
}

key::Window::~Window() {

}

void key::Window::run() {
	auto sdl_available = SDLInit();

	if (sdl_available) {



		SDLQuit();
	}
}