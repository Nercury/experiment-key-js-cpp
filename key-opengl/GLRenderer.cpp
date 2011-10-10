#include "GLRenderer.h"

#include <set>
#include <map>

#include <key-opengl/GLWindow.h>
#include <key-window/Window.h>

using namespace std;
using namespace key;

bool GLRenderer::screenSaverEnabled = true;

static int window_instances = 0;

fun_res GLRenderer::useSDL() {
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		return fun_error(boost::format("Failed to initialize SDL: %1%") % SDL_GetError());
	} else {
		SDL_StartTextInput();
		GLRenderer::setGlobalSDLValues();
	}
		
	window_instances++;
	return fun_ok();
}

void GLRenderer::unuseSDL() {
	if (window_instances == 1)
	{
		SDL_Quit();
	}
	window_instances--;
}

void GLRenderer::setGlobalSDLValues() {
	if (window_instances > 0) {
		if (SDL_IsScreenSaverEnabled() == SDL_TRUE) {
			if (!GLRenderer::screenSaverEnabled)
				SDL_DisableScreenSaver();
		} else {
			if (GLRenderer::screenSaverEnabled)
				SDL_EnableScreenSaver();
		}
	}
}

bool GLRenderer::isScreenSaverEnabled() {
	return GLRenderer::screenSaverEnabled;
}

void GLRenderer::setScreenSaverEnabled(bool value) {
	GLRenderer::screenSaverEnabled = value;
	GLRenderer::setGlobalSDLValues();
}

uint16_t GLRenderer::getNumDisplays() {
	useSDL();
	auto res = SDL_GetNumVideoDisplays();
	unuseSDL();
	if (res >= 1)
		return (uint16_t)res;
	std::cout << "Error getting number of displays. " << SDL_GetError() << endl;
	return 0;
}


void GLRenderer::getDisplayModes(uint16_t displayIndex, std::list<std::map<std::string, int32_t>> & modes) {
	useSDL();

	auto num_displays = getNumDisplays();
	if (displayIndex < num_displays) {
		auto num_display_modes = SDL_GetNumDisplayModes((int)displayIndex);
		cout << SDL_GetError() << endl;
		if (num_display_modes >= 1) {
			SDL_DisplayMode mode;
			std::set<std::string> existing;
			for (int i = 0; i < num_display_modes; i++) {
				SDL_GetDisplayMode((int)displayIndex, i, &mode);
				std::string mode_key = (boost::format("%1%%2%%3%") % mode.w % mode.h % mode.refresh_rate).str();
				auto it = existing.find(mode_key);
				if (it == existing.end()) {
					std::map<std::string, int32_t> new_mode;
					new_mode.insert(pair<std::string, int32_t>("width", mode.w));
					new_mode.insert(pair<std::string, int32_t>("height", mode.h));
					new_mode.insert(pair<std::string, int32_t>("refreshRate", mode.refresh_rate));
					modes.push_back(new_mode);
					existing.insert(mode_key);
				}
			}
		}
	}

	unuseSDL();
}

std::map<std::string, int32_t> GLRenderer::getDesktopDisplayMode(uint16_t displayIndex) {
	useSDL();

	SDL_DisplayMode mode;
	std::map<std::string, int32_t> dt_mode;

	if (SDL_GetDesktopDisplayMode((int)displayIndex, &mode) == 0) {
		
		dt_mode.insert(pair<std::string, int32_t>("width", mode.w));
		dt_mode.insert(pair<std::string, int32_t>("height", mode.h));
		dt_mode.insert(pair<std::string, int32_t>("refreshRate", mode.refresh_rate));

	} else {
		cout << "Failed to get desktop display mode. " << SDL_GetError() << endl;
	}

	unuseSDL();

	return dt_mode;
}

bool GLRenderer::addWindow(v8::Handle<v8::Object> v8_window) 
{
	auto persistent_w = make_shared<PersistentV8<Window>>(v8_window);

	uint64_t id = persistent_w->NativeObject()->getId();
	auto existingIt = this->openedWindows.find(id);
	if (existingIt != this->openedWindows.end())
		return false;

	this->openedWindows.insert(pair<uint64_t, shared_ptr<PersistentV8<Window>>>(id, persistent_w));
	return true;
}

bool GLRenderer::removeWindow(uint64_t id)
{
	auto existingIt = this->openedWindows.find(id);
	if (existingIt == this->openedWindows.end())
		return false;
	this->openedWindows.erase(existingIt);
	return true;
}

bool GLRenderer::runWindowLoop()
{
	for (auto it = this->openedWindows.begin(); it != this->openedWindows.end(); ++it)
	{
		cout << "Window " << it->first << endl;
	}
	return true;
}

/**
 * @brief Try to get with, height, refresh values from mode value map
 */
bool GLRenderer::parseDisplayMode(std::map<std::string, int32_t> modeValues, int & w, int & h, int & refreshRate) {
	auto withIt = modeValues.find("width");
	auto heightIt = modeValues.find("height");
	auto refreshRateIt = modeValues.find("refreshRate");
	if (withIt == modeValues.end() || heightIt == modeValues.end() || refreshRateIt == modeValues.end())
		return false;
	w = withIt->second;
	h = heightIt->second;
	refreshRate = refreshRateIt->second;
	return true;
}