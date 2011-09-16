#include "Window.h"

#include <key-v8/exception.h>

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

namespace cvv8 {
    CVV8_TypeName_IMPL((key::Window),"Window");
}

key::Window::~Window() {
	if (!onWindowInit.IsEmpty())
		onWindowInit.Dispose();
}

void key::Window::run(const Arguments & args) {
	auto sdl_available = SDLInit();

	if (sdl_available) {
		auto This = args.This();

		if (onWindowInit.IsEmpty()) {
			cout << "Window init is empty" << endl;
		} else {
			Handle<Value> result = onWindowInit->Call(This, 0, NULL); 
		}

		SDLQuit();
	}
}

Handle<Value> key::Window::getOnWindowInit() {
	return this->onWindowInit;
}

void key::Window::setOnWindowInit(Handle<Value> value) {
	HandleScope handle_scope;
	if (value->IsFunction()) {
		auto func = Handle<Function>::Cast(value);
		this->onWindowInit = Persistent<Function>::New(func);
	} else
		cout << "Warning! Tried to set non-function as onWindowInit event callback!" << endl;
}

void key::Window::setWindowTitle(std::string newTitle) {
	this->windowTitle = windowTitle;
}