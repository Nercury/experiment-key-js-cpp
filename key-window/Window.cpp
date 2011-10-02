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

key::Window::Window() 
	: windowTitle("Key Window"), 
	device(), fullScreen(false), hidden(false), resizable(true) {
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
	if (this->device.use_count() > 0)
		this->device->notifyWindowChange(NOTIFY_CHANGE_TITLE);
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

	auto renderer = getCurrentRenderer();
	if (renderer.use_count() > 0)
		renderer->getDisplayModes(displayIndex, modes);
	
	return modes;
}

void key::Window::setDisplayMode(v8::Handle<v8::Value> newMode) {
	HandleScope scope;

	if (newMode->IsObject()) {
		this->displayMode.clear();
		auto modeObj = newMode->ToObject();
		auto propertyNames = modeObj->GetPropertyNames();
		for (uint32_t i = 0; i < propertyNames->Length(); i++) {
			auto name = propertyNames->Get(i);
			auto value = modeObj->Get(name);
			this->displayMode[cvv8::CastFromJS<std::string>(name)] = cvv8::CastFromJS<int32_t>(value);
		}

		if (this->device.use_count() > 0)
			this->device->notifyWindowChange(NOTIFY_CHANGE_DISPLAY_MODE);
	}
}

void key::Window::setFullScreen(bool value) {
	this->fullScreen = value;

	if (this->device.use_count() > 0)
		this->device->notifyWindowChange(NOTIFY_CHANGE_FULL_SCREEN);
}

void key::Window::setHidden(bool value) {
	this->hidden = value;

	if (this->device.use_count() > 0)
		this->device->notifyWindowChange(NOTIFY_CHANGE_HIDDEN);
}

void key::Window::setResizable(bool value) {
	this->resizable = value;

	if (this->device.use_count() > 0)
		this->device->notifyWindowChange(NOTIFY_CHANGE_RESIZABLE);
}

void key::Window::setMinimized(bool value) {
	this->minimized = value;

	if (this->device.use_count() > 0)
		this->device->notifyWindowChange(NOTIFY_CHANGE_MINIMIZED);
}

void key::Window::setMaximized(bool value) {
	this->maximized = value;

	if (this->device.use_count() > 0)
		this->device->notifyWindowChange(NOTIFY_CHANGE_MAXIMIZED);
}

void key::Window::setInputGrabbed(bool value) {
	this->inputGrabbed = value;

	if (this->device.use_count() > 0)
		this->device->notifyWindowChange(NOTIFY_CHANGE_INPUT_GRAB);
}

void key::Window::setWindowSize(std::list<int32_t> value) {
	this->windowSize = value;

	if (this->device.use_count() > 0)
		this->device->notifyWindowChange(NOTIFY_CHANGE_WINDOW_SIZE);
}