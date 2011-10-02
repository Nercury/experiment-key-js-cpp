#include "OpenGLInstance.h"

#include <iostream>

#include <boost/format.hpp> 

#include <key-opengl/OpenGL.h>

using namespace std;
using namespace key;

OpenGLInstance::OpenGLInstance(key::Window * window) 
	: sdl_window(NULL), key_window(window), width(800), height(600), running(false) {

}

void OpenGLInstance::notifyWindowChange() {
	//this->window_title = new_title;
}

void OpenGLInstance::unsetWindow() {
	this->key_window = NULL;
	this->running = false;
}

void OpenGLInstance::handleEvent(SDL_Event &evt, float dt)
{
    if (evt.type == SDL_QUIT)
        running = false;
}

void OpenGLInstance::resize()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width, height, 0.0f, 0.0f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);

	glClearColor(0.3f, 0.6f, 0.9f, 1.0f);
}

void OpenGLInstance::update(float dt)
{
    /* TODO */
}

void OpenGLInstance::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

fun_res OpenGLInstance::run() {
	auto sdl_init_result = OpenGL::useSDL();
	if (sdl_init_result.not_ok())
		return sdl_init_result;

	cout << "Using SDL " << SDL_MAJOR_VERSION << "." << SDL_MINOR_VERSION << "." << SDL_PATCHLEVEL << "." << endl;

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

	SDL_Event evt;
    uint64_t old = SDL_GetPerformanceCounter();

	this->running = true;

	this->resize();

	while (running) {
		uint64_t now = SDL_GetPerformanceCounter();
        float dt = (now - old) / (float)SDL_GetPerformanceFrequency();
        old = now;

        if (dt > 0.1f)
            dt = 0.0016f;

        while (SDL_PollEvent(&evt))
            this->handleEvent(evt, dt);

        if (dt > 0.0f)
            this->update(dt);
        this->render();

		SDL_GL_SwapWindow(sdl_window);
        SDL_Delay(1);
	}

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(sdl_window);

	sdl_window = NULL;

	OpenGL::unuseSDL();
	return fun_ok();
}