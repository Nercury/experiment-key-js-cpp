#include "Window.h"

#include <key-v8/exception.h>
#include <key-window/Renderer.h>

#include <iostream>

using namespace key;
using namespace std;
namespace cv = cvv8;
using namespace v8;

namespace cvv8 {
    CVV8_TypeName_IMPL((key::Window),"Window");
}

key::Window::Window() : windowTitle("Key Window"), device(NULL) {
	auto all_devices = Renderer::getInstances();
	for (auto it = all_devices.begin(); it != all_devices.end(); ++it) {
		this->allRenderDevices.push_back(it->first);
	}
}

key::Window::~Window() {
	if (!onWindowInit.IsEmpty())
		onWindowInit.Dispose();
}

void key::Window::run(const Arguments & args) {
	//auto all_devices = Renderer::getOne(this->);


	/*auto sdl_available = SDLInit();

	if (sdl_available) {*/
		auto This = args.This();

		if (onWindowInit.IsEmpty()) {
			cout << "Window init is empty" << endl;
		} else {
			Handle<Value> result = onWindowInit->Call(This, 0, NULL); 
		}

		/*SDLQuit();
	}*/
}

void key::Window::setOnWindowInit(Handle<Value> value) {
	HandleScope handle_scope;
	if (value->IsFunction()) {
		auto func = Handle<Function>::Cast(value);
		this->onWindowInit = Persistent<Function>::New(func);
	} else
		cout << "Warning! Tried to set non-function as onWindowInit event callback!" << endl;
}

void key::Window::setOnWindowResize(Handle<Value> value) {
	HandleScope handle_scope;
	if (value->IsFunction()) {
		auto func = Handle<Function>::Cast(value);
		this->onWindowResize = Persistent<Function>::New(func);
	} else
		cout << "Warning! Tried to set non-function as onWindowResize event callback!" << endl;
}

void key::Window::setWindowTitle(std::string newTitle) {
	this->windowTitle = windowTitle;
}