#include "Window.h"

#include <boost/assign.hpp>

#include <key-v8/exception.h>
#include <key-window/Renderer.h>
#include <key-v8/PersistentV8.h>

#include <functional>
#include <algorithm>
#include <iostream>

using namespace key;
using namespace std;
namespace cv = cvv8;
using namespace v8;

namespace cvv8 {
    CVV8_TypeName_IMPL((key::Window),"Window");
}

static uint64_t next_window_id = 0;

static uint64_t get_next_window_id() {
	next_window_id++;
	return next_window_id;
}

static void make_weak_callback(v8::Persistent<v8::Value> object, void *parameter);

key::Window::Window(const v8::Arguments & args) : 
	windowTitle("Key Window"), 
	id(get_next_window_id()),
	isOpened(false),
	displayIndex(0),
	fullScreen(false), 
	hidden(false), 
	resizable(true),
	inputGrabbed(false),
	maximized(false),
	minimized(false) 
{
	this->windowSize = boost::assign::list_of(640)(480);

	this->allRenderers = Renderer::getRenderers();
	for (auto it = this->allRenderers.begin(); it != this->allRenderers.end(); ++it) {
		if (it == this->allRenderers.begin())
			this->currentDevice = it->first;
		this->allRenderDevices.push_back(it->first);
	}

	this->jsObject = v8::Persistent<v8::Value>::New(args.This());
	this->jsObject.MakeWeak(NULL, make_weak_callback);
}

static void make_weak_callback(v8::Persistent<v8::Value> object, void *parameter) {
	object.Dispose(); // if there is no reference from js, surelly this can be disposed.
	object.Clear();
}

key::Window::~Window() {
	if (!onWindowInit.IsEmpty())
		onWindowInit.Dispose();
	if (!onWindowResize.IsEmpty())
		onWindowResize.Dispose();
	if (!onMouseMotion.IsEmpty())
		onMouseMotion.Dispose();
	// js object gets disposed on weak ref callback.
}

void key::Window::setCurrentDevice(std::string value) {
	if (this->isOpened) {
		// might be possible, but could overcomplicate already messy code :)
		cout << "Can not change render device while window is opened." << endl;
	} else {
		this->currentDevice = value;
	}
}

std::shared_ptr<key::Renderer> key::Window::getCurrentRenderer() {
	auto it = this->allRenderers.find(this->currentDevice);
	if (it == this->allRenderers.end()) {
		cout << "Render device " << this->currentDevice << " was not found." << endl;
		return std::shared_ptr<Renderer>();
	} else
		return it->second;
}

bool key::Window::open(const v8::Arguments & args) 
{
	if (isOpened)
		return false;

	auto renderer = getCurrentRenderer();
	if (renderer.use_count() == 0)
		return false;

	HandleScope handle_scope;

	Handle<Object> v8_window = args.This();

	if (renderer->addWindow(v8_window)) {
		this->isOpened = true;
		return true;
	}

	return false;
}

bool key::Window::close() 
{
	if (!isOpened)
		return false;

	auto renderer = getCurrentRenderer();
	if (renderer.use_count() == 0)
		return false;

	if (renderer->removeWindow(this->id)) {
		this->isOpened = false;
		return true;
	}

	return false;
}

bool key::Window::run(const v8::Arguments & args) 
{
	cout << "Current device is " << (this->currentDevice.empty() ? "empty" : this->currentDevice) << endl;

	if (this->currentDevice.empty()) {
		cout << "Can not initialize window on empty device." << endl;
		return false;
	} else {
		auto renderer = getCurrentRenderer();
		if (renderer.use_count() > 0) {
			if (!this->isOpened)
				this->open(args);

			if (!this->isOpened)
			{
				cout << "Can not run closed window." << endl;
				return false;
			}

			return renderer->runWindowLoop(jsObject.As<v8::Object>()->CreationContext());
		}
	}

	return true;
}

void key::Window::setOnMouseMotion(Handle<Value> value) {
	HandleScope handle_scope;
	if (value->IsFunction()) {
		auto func = Handle<Function>::Cast(value);
		this->onMouseMotion = Persistent<Function>::New(func);
	} else
		cout << "Warning! Tried to set non-function as onMouseMotion event callback!" << endl;
}

void key::Window::setOnKeyUp(Handle<Value> value) {
	HandleScope handle_scope;
	if (value->IsFunction()) {
		auto func = Handle<Function>::Cast(value);
		this->onKeyUp = Persistent<Function>::New(func);
	} else
		cout << "Warning! Tried to set non-function as onKeyUp event callback!" << endl;
}

void key::Window::setOnKeyDown(Handle<Value> value) {
	HandleScope handle_scope;
	if (value->IsFunction()) {
		auto func = Handle<Function>::Cast(value);
		this->onKeyDown = Persistent<Function>::New(func);
	} else
		cout << "Warning! Tried to set non-function as onKeyDown event callback!" << endl;
}

void key::Window::setOnWindowClose(Handle<Value> value) {
	HandleScope handle_scope;
	if (value->IsFunction()) {
		auto func = Handle<Function>::Cast(value);
		this->onWindowClose = Persistent<Function>::New(func);
	} else
		cout << "Warning! Tried to set non-function as onWindowClose event callback!" << endl;
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
	/*if (this->device.use_count() > 0)
		this->device->notifyWindowChange(NOTIFY_CHANGE_TITLE);*/
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

		/*if (this->device.use_count() > 0)
			this->device->notifyWindowChange(NOTIFY_CHANGE_DISPLAY_MODE);*/
	}
}

std::map<std::string, int32_t> key::Window::getDesktopDisplayMode() {
	auto renderer = getCurrentRenderer();
	if (renderer.use_count() > 0)
		return renderer->getDesktopDisplayMode(this->displayIndex);
	std::map<std::string, int32_t> empty;
	return empty;
}

void key::Window::setDisplayIndex(uint16_t value) {
	this->displayIndex = value;

	/*if (this->device.use_count() > 0)
		this->device->notifyWindowChange(NOTIFY_CHANGE_DISPLAY_INDEX);*/
}

void key::Window::setFullScreen(bool value) {
	this->fullScreen = value;

	/*if (this->device.use_count() > 0)
		this->device->notifyWindowChange(NOTIFY_CHANGE_FULL_SCREEN);*/
}

void key::Window::setHidden(bool value) {
	this->hidden = value;

	/*if (this->device.use_count() > 0)
		this->device->notifyWindowChange(NOTIFY_CHANGE_HIDDEN);*/
}

void key::Window::setResizable(bool value) {
	this->resizable = value;

	/*if (this->device.use_count() > 0)
		this->device->notifyWindowChange(NOTIFY_CHANGE_RESIZABLE);*/
}

void key::Window::setMinimized(bool value) {
	this->minimized = value;

	/*if (this->device.use_count() > 0)
		this->device->notifyWindowChange(NOTIFY_CHANGE_MINIMIZED);*/
}

void key::Window::setMaximized(bool value) {
	this->maximized = value;

	/*if (this->device.use_count() > 0)
		this->device->notifyWindowChange(NOTIFY_CHANGE_MAXIMIZED);*/
}

void key::Window::setInputGrabbed(bool value) {
	this->inputGrabbed = value;

	/*if (this->device.use_count() > 0)
		this->device->notifyWindowChange(NOTIFY_CHANGE_INPUT_GRAB);*/
}

void key::Window::setWindowSize(std::vector<int32_t> value) {
	if (value.size() != 2)
		return;

	this->windowSize = value;

	/*if (this->device.use_count() > 0)
		this->device->notifyWindowChange(NOTIFY_CHANGE_WINDOW_SIZE);*/
}