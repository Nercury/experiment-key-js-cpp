#include "SDLWindowInfo.h"

using namespace key;

void SDLWindowInfo::makeCurrent()
{
	SDL_GL_MakeCurrent(sdlWindow, context);
}

void SDLWindowInfo::render()
{
	this->makeCurrent();

	glClearColor(0.2,0.2,0.2,0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	SDL_GL_SwapWindow(this->sdlWindow);
}