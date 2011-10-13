#include "SDLWindowInfo.h"

using namespace key;

void SDLWindowInfo::makeCurrent()
{
	SDL_GL_MakeCurrent(sdlWindow, context);
}

void SDLWindowInfo::resize()
{
	this->makeCurrent();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(0.0f, renderWidth, renderHeight, 0.0f, 0.0f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
}

void SDLWindowInfo::render()
{
	this->makeCurrent();

	glClearColor(0.3f, 0.6f, 0.9f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
        glColor3f(1, 0, 0); glVertex3f(0, 0, 0);
        glColor3f(1, 1, 0); glVertex3f(100, 0, 0);
        glColor3f(1, 0, 1); glVertex3f(100, 100, 0);
        glColor3f(1, 1, 1); glVertex3f(0, 100, 0);
    glEnd();

	glFlush();

	SDL_GL_SwapWindow(this->sdlWindow);
}