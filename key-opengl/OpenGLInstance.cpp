#include "OpenGLInstance.h"

#include <iostream>

#include <boost/format.hpp> 

using namespace std;
using namespace key;

static bool sdl_initialized = false;
static int window_instances = 0;

static fun_res SDLInit()
{
	if (window_instances == 0)
	{
		if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		{
			return fun_error(boost::format("Failed to initialize SDL: %1%") % SDL_GetError());
		} else {
			SDL_StartTextInput();
			cout << "SDL " << SDL_MAJOR_VERSION << "." << SDL_MINOR_VERSION << "." << SDL_PATCHLEVEL << " initialized." << endl;
		}
		window_instances++;
	}
	return fun_ok();
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
	auto sdl_init_result = SDLInit();
	if (sdl_init_result.not_ok())
		return sdl_init_result;




	SDLQuit();
	return fun_ok();
}