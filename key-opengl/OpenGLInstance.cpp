#include "OpenGLInstance.h"

#include <iostream>

#include <boost/format.hpp> 
#include <boost/date_time/posix_time/posix_time.hpp>

#include <key-opengl/OpenGL.h>

using namespace std;
using namespace key;

OpenGLInstance::OpenGLInstance(key::Window * window) 
	: sdl_window(NULL), key_window(window), width(800), height(600), running(false) {

}

void OpenGLInstance::notifyWindowChange(int16_t window_change) {
	//this->window_title = new_title;
}

void OpenGLInstance::unsetWindow() {
	this->key_window = NULL;
	this->running = false;
}

void OpenGLInstance::handleEvent(SDL_Event &evt, int64_t dt)
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

void OpenGLInstance::update(int64_t dt)
{
    /* TODO */
}

void OpenGLInstance::render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
        glColor3f(1, 0, 0); glVertex3f(0, 0, 0);
        glColor3f(1, 1, 0); glVertex3f(100, 0, 0);
        glColor3f(1, 0, 1); glVertex3f(100, 100, 0);
        glColor3f(1, 1, 1); glVertex3f(0, 100, 0);
    glEnd();
}

fun_res OpenGLInstance::run() {
	auto sdl_init_result = OpenGL::useSDL();
	if (sdl_init_result.not_ok())
		return sdl_init_result;

	cout << "Using SDL " << SDL_MAJOR_VERSION << "." << SDL_MINOR_VERSION << "." << SDL_PATCHLEVEL << "." << endl;

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
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

	int seconds = 0;
	uint64_t second_dt = 0;

	const int secs_for_avg = 8;
	int sec_frames[secs_for_avg] = {0, 0, 0};

	boost::posix_time::ptime last_time = boost::posix_time::microsec_clock::local_time();
	boost::posix_time::ptime new_time;
	boost::posix_time::ptime last_second_time = last_time;

	float dt = 0;

	while (running) {
		new_time = boost::posix_time::microsec_clock::local_time();
		int64_t dt = (new_time - last_time).total_microseconds();
		last_time = new_time;

        while (SDL_PollEvent(&evt))
            this->handleEvent(evt, dt);

        if (dt > 0)
            this->update(dt);
        this->render();

		SDL_GL_SwapWindow(sdl_window);
        //SDL_Delay(5);

		sec_frames[0]++;

		if ((new_time - last_second_time).total_microseconds() >= 1000000)
		{
			if (seconds < secs_for_avg)
				seconds++;
			int sum = 0;
			for (int x = 0; x < seconds; x++) {
				sum += sec_frames[x];
			}

			cout << "AVG FPS: " << (sum / seconds) << endl;

			last_second_time = new_time;
			for (int x = secs_for_avg - 1; x > 0; x--) {
				sec_frames[x] = sec_frames[x - 1];
			}
			sec_frames[0] = 0;
		}
	}

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(sdl_window);

	sdl_window = NULL;

	OpenGL::unuseSDL();
	return fun_ok();
}