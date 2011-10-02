#include "OpenGL.h"

#include <set>

#include <key-opengl/OpenGLInstance.h>
#include <key-window/Window.h>

using namespace key;
using namespace std;

bool OpenGL::screenSaverEnabled = true;

fun_res_obj<DeviceInstance> OpenGL::createDevice(key::Window * window) {
	OpenGLInstance * device = new OpenGLInstance(window);
	shared_ptr<DeviceInstance> instance(device);

	// todo: pass settings to device.
	
	return fun_ok(instance);
}

static int window_instances = 0;

fun_res OpenGL::useSDL() {
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		return fun_error(boost::format("Failed to initialize SDL: %1%") % SDL_GetError());
	} else {
		SDL_StartTextInput();
		OpenGL::setGlobalSDLValues();
	}
		
	window_instances++;
	return fun_ok();
}

void OpenGL::unuseSDL() {
	if (window_instances == 1)
	{
		SDL_Quit();
	}
	window_instances--;
}

void OpenGL::setGlobalSDLValues() {
	if (window_instances > 0) {
		if (SDL_IsScreenSaverEnabled() == SDL_TRUE) {
			if (!OpenGL::screenSaverEnabled)
				SDL_DisableScreenSaver();
		} else {
			if (OpenGL::screenSaverEnabled)
				SDL_EnableScreenSaver();
		}
	}
}

bool OpenGL::isScreenSaverEnabled() {
	return OpenGL::screenSaverEnabled;
}

void OpenGL::setScreenSaverEnabled(bool value) {
	OpenGL::screenSaverEnabled = value;
	OpenGL::setGlobalSDLValues();
}

uint16_t OpenGL::getNumDisplays() {
	useSDL();
	auto res = SDL_GetNumVideoDisplays();
	unuseSDL();
	if (res >= 1)
		return (uint16_t)res;
	std::cout << "Error getting number of displays. " << SDL_GetError() << endl;
	return 0;
}

void OpenGL::getDisplayModes(uint16_t displayIndex, std::list<std::map<std::string, int32_t>> & modes) {
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
				std::string mode_key = (boost::format("%1%%2%%3%%4%") % mode.w % mode.h % mode.refresh_rate % mode.format).str();
				auto it = existing.find(mode_key);
				if (it == existing.end()) {
					std::map<std::string, int32_t> new_mode;
					new_mode.insert(pair<std::string, int32_t>("width", mode.w));
					new_mode.insert(pair<std::string, int32_t>("height", mode.h));
					new_mode.insert(pair<std::string, int32_t>("refreshRate", mode.refresh_rate));
					new_mode.insert(pair<std::string, int32_t>("format", mode.format));
					modes.push_back(new_mode);
					existing.insert(mode_key);
				}
			}
		}
	}

	unuseSDL();
}