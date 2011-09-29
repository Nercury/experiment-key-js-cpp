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
	auto all_renderers = Renderer::getRenderers();
	for (auto it = all_renderers.begin(); it != all_renderers.end(); ++it) {
		if (it == all_renderers.begin())
			this->currentDevice = it->first;
		this->allRenderDevices.push_back(it->first);
	}
}

key::Window::~Window() {
	if (!onWindowInit.IsEmpty())
		onWindowInit.Dispose();
}

bool key::Window::run() {
	cout << "Current device is " << (this->currentDevice.empty() ? "empty" : this->currentDevice) << endl;

	if (this->currentDevice.empty()) {
		cout << "Can not initialize window on empty device" << endl;
		return false;
	} else {
		auto all_renderers = Renderer::getRenderers();
		auto it = all_renderers.find(this->currentDevice);
		if (it == all_renderers.end()) {
			cout << "Render device " << this->currentDevice << " was not found" << endl;
		} else {
			auto renderer = it->second;
			cout << "Creating " << renderer->getName() << "..." << endl;
			auto device_result = renderer->createDevice();
			if (device_result.ok()) {
				this->device = device_result.result;
				auto run_result = this->device->run();
				if (run_result.not_ok()) {
					cout << run_result.message() << endl;
					return false;
				}
			} else {
				cout << device_result.message() << endl;
				return false;
			}
		}

		/*if (onWindowInit.IsEmpty()) {
			cout << "Window init is empty" << endl;
		} else {
			Handle<Value> result = onWindowInit->Call(v8::Object::New(), 0, NULL); 
		}*/
	}

	return true;
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