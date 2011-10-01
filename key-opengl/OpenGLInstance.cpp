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

OpenGLInstance::OpenGLInstance(key::Window * window) 
	: sdl_window(NULL), key_window(window), width(800), height(600) {

}

void OpenGLInstance::notifyWindowChange() {
	//this->window_title = new_title;
}


fun_res OpenGLInstance::run() {
	auto sdl_init_result = SDLInit();
	if (sdl_init_result.not_ok())
		return sdl_init_result;

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	sdl_window = SDL_CreateWindow(this->key_window->windowTitle.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width, height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!sdl_window)
		return fun_error(boost::format("Unable to create render window. %1%") % SDL_GetError());

    context = SDL_GL_CreateContext(sdl_window);
    SDL_GL_SetSwapInterval(1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width, height, 0.0f, 0.0f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);

    //mainloop();

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(sdl_window);

	sdl_window = NULL;

	SDLQuit();
	return fun_ok();
}