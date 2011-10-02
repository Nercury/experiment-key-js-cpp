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
	this->allRenderers = Renderer::getRenderers();
	for (auto it = this->allRenderers.begin(); it != this->allRenderers.end(); ++it) {
		if (it == this->allRenderers.begin())
			this->currentDevice = it->first;
		this->allRenderDevices.push_back(it->first);
	}
}

key::Window::~Window() {
	if (!onWindowInit.IsEmpty())
		onWindowInit.Dispose();
}

std::shared_ptr<key::Renderer> key::Window::getCurrentRenderer() {
	auto it = this->allRenderers.find(this->currentDevice);
	if (it == this->allRenderers.end()) {
		cout << "Render device " << this->currentDevice << " was not found." << endl;
		return std::shared_ptr<Renderer>();
	} else
		return it->second;
}

bool key::Window::run() {
	cout << "Current device is " << (this->currentDevice.empty() ? "empty" : this->currentDevice) << endl;

	if (this->currentDevice.empty()) {
		cout << "Can not initialize window on empty device" << endl;
		return false;
	} else {
		auto renderer = getCurrentRenderer();
		if (renderer.use_count() > 0) {
			cout << "Creating " << renderer->getName() << "..." << endl;
			auto device_result = renderer->createDevice(this);
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
	this->windowTitle = newTitle;
}

void key::Window::setScreenSaverEnabled(bool value) {
	auto renderer = getCurrentRenderer();
	if (renderer.use_count() > 0)
		renderer->setScreenSaverEnabled(value);
}

bool key::Window::getScreenSaverEnabled() {
	auto renderer = getCurrentRenderer();
	if (renderer.use_count() > 0)
		return renderer->isScreenSaverEnabled();
	return true;
}

uint16_t key::Window::getNumDisplays() {
	auto renderer = getCurrentRenderer();
	if (renderer.use_count() > 0)
		return renderer->getNumDisplays();
	return 0;
}

std::list<std::map<std::string, int32_t>> key::Window::getDisplayModes(uint16_t displayIndex) {
	std::list<std::map<std::string, int32_t>> modes;

	{
	std::map<std::string, int32_t> mode;
	mode.insert(pair<std::string, int32_t>("width", 640));
	mode.insert(pair<std::string, int32_t>("height", 480));
	modes.push_back(mode);
	}

	{
	std::map<std::string, int32_t> mode;
	mode.insert(pair<std::string, int32_t>("width", 800));
	mode.insert(pair<std::string, int32_t>("height", 600));
	modes.push_back(mode);
	}

	return modes;
}