#include "GLRenderer.h"

#include <set>
#include <map>

#include <boost/assign.hpp>

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
	cout << "add window" << endl;

	auto persistent_w = make_shared<PersistentV8<Window>>(v8_window);

	uint64_t id = persistent_w->NativeObject()->getId();
	auto idExists = false;
	for (auto it = this->openedWindows.cbegin(); it != openedWindows.cend(); ++it) {
		if (it->refV8->NativeObject()->getId() == id) {
			idExists = true;
			break;
		}
	}

	if (idExists)
		return false;

	SDLWindowInfo wi(persistent_w);

	if (this->createWindow(wi)) {
		this->openedWindows.push_back(wi);
		return true;
	} else {
		return false;
	}
}

bool GLRenderer::removeWindow(uint64_t id)
{
	for (auto it = this->openedWindows.begin(); it != openedWindows.end(); ++it) {
		if (it->refV8->NativeObject()->getId() == id) {
			auto wi = *it;
			this->openedWindows.erase(it);
			destroyWindow(wi);
			return true;
		}
	}
	
	return false;
}

bool GLRenderer::createWindow(SDLWindowInfo & wi) {
	// if first window, initialize SDL/GL stuff
	if (this->openedWindows.size() == 0) {
		cout << "Use SDL" << endl;
		auto sdl_init_result = GLRenderer::useSDL();
		if (sdl_init_result.not_ok()) {
			cout << "Failed to use SDL. " << sdl_init_result.message() << endl;
			return false;
		}

		cout << boost::format("Using SDL %1%.%2%.%3%.") 
		% SDL_MAJOR_VERSION % SDL_MINOR_VERSION % SDL_PATCHLEVEL << endl;

		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	}

	uint32_t windowFlags = SDL_WINDOW_OPENGL;

	auto keyWindow = wi.refV8->NativeObject();

	if (keyWindow->fullScreen)
		windowFlags |= SDL_WINDOW_FULLSCREEN;

	if (!keyWindow->fullScreen) {

		if (keyWindow->hidden)
			windowFlags |= SDL_WINDOW_HIDDEN;
		else
			windowFlags |= SDL_WINDOW_SHOWN;

		if (keyWindow->resizable)
			windowFlags |= SDL_WINDOW_RESIZABLE;

		if (keyWindow->minimized)
			windowFlags |= SDL_WINDOW_MINIMIZED;

		if (keyWindow->maximized)
			windowFlags |= SDL_WINDOW_MAXIMIZED;

		if (keyWindow->inputGrabbed)
			windowFlags |= SDL_WINDOW_INPUT_GRABBED;
	}

	// widow width and height are only for windowed mode, for
	// fullscreen display mode is used

	if (keyWindow->fullScreen) {
		SDL_DisplayMode dm;
		dm.format = SDL_PIXELFORMAT_UNKNOWN;
		dm.driverdata = 0;
		if (!GLRenderer::parseDisplayMode(keyWindow->displayMode, dm.w, dm.h, dm.refresh_rate)) {
			dm.w = keyWindow->windowSize[0];
			dm.h = keyWindow->windowSize[1];
			dm.refresh_rate = 100;
		}
		SDL_DisplayMode final_dm;
		if (SDL_GetClosestDisplayMode(keyWindow->displayIndex, &dm, &final_dm) == NULL) {
			this->unuseSdlIfNoWindows();
			cout << boost::format("Unable to create render window. %1%") % SDL_GetError() << endl;
			return false;
		}
		wi.renderWidth = final_dm.w;
		wi.renderHeight = final_dm.h;

		keyWindow->displayMode["width"] = final_dm.w;
		keyWindow->displayMode["height"] = final_dm.h;
		keyWindow->displayMode["refreshRate"] = final_dm.refresh_rate;

		keyWindow->windowSize = boost::assign::list_of(wi.renderWidth)(wi.renderHeight);
	} else {
		wi.renderWidth = keyWindow->windowSize[0];
		wi.renderHeight = keyWindow->windowSize[1];
	}

	wi.sdlWindow = SDL_CreateWindow(keyWindow->windowTitle.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			wi.renderWidth, wi.renderHeight,
			windowFlags);

	if (wi.sdlWindow == 0) {
		this->unuseSdlIfNoWindows();
		cout << boost::format("Failed to create a window. %1%") % SDL_GetError() << endl;
		return false;
	}

	wi.sdlWindowID = SDL_GetWindowID(wi.sdlWindow);

	wi.context = SDL_GL_CreateContext(wi.sdlWindow);
	wi.makeCurrent();

	SDL_GL_SetSwapInterval(1);

	return true;
}

void SDLWindowInfo::makeCurrent()
{
	SDL_GL_MakeCurrent(sdlWindow, context);
}

void GLRenderer::destroyWindow(SDLWindowInfo & wi) {
	SDL_GL_DeleteContext(wi.context);
	SDL_DestroyWindow(wi.sdlWindow);

	this->unuseSdlIfNoWindows();
}

void GLRenderer::unuseSdlIfNoWindows() {
	if (this->openedWindows.size() == 0) {
		cout << "unuse SDL" << endl;
		unuseSDL();
	}
}

bool GLRenderer::runWindowLoop()
{
	auto runResult = true;

	SDL_Event event;

	int seconds = 0; // second count for measuring average fps
	uint64_t second_dt = 0;

	const int secs_for_avg = 8;
	int sec_frames[secs_for_avg] = {0, 0, 0};

	vector<SDLWindowInfo>::iterator it;

	boost::posix_time::ptime lastTime = boost::posix_time::microsec_clock::local_time();
	boost::posix_time::ptime newTime;
	boost::posix_time::ptime lastSecondTime = boost::posix_time::microsec_clock::local_time();

	while (this->openedWindows.size() > 0)
	{
		newTime = boost::posix_time::microsec_clock::local_time();
		int64_t dt = (newTime - lastTime).total_microseconds();
		lastTime = newTime;

		while (SDL_PollEvent(&event)) {
			//SDL_EventType::
			
			switch (event.type)
			{
			case SDL_WINDOWEVENT:
				for (it = this->openedWindows.begin(); it != this->openedWindows.end(); ++it) {
					if (it->sdlWindowID == event.window.windowID) {
						switch (event.window.event)
						{
							case SDL_WINDOWEVENT_SHOWN:
								fprintf(stderr, "Window %d shown\n", event.window.windowID);
								break;
							case SDL_WINDOWEVENT_HIDDEN:
								fprintf(stderr, "Window %d hidden\n", event.window.windowID);
								break;
							case SDL_WINDOWEVENT_EXPOSED:
								fprintf(stderr, "Window %d exposed\n", event.window.windowID);
								break;
							case SDL_WINDOWEVENT_MOVED:
								fprintf(stderr, "Window %d moved to %d,%d\n",
										event.window.windowID, event.window.data1,
										event.window.data2);
								break;
							case SDL_WINDOWEVENT_RESIZED:
								fprintf(stderr, "Window %d resized to %dx%d\n",
										event.window.windowID, event.window.data1,
										event.window.data2);
								break;
							case SDL_WINDOWEVENT_MINIMIZED:
								fprintf(stderr, "Window %d minimized\n", event.window.windowID);
								break;
							case SDL_WINDOWEVENT_MAXIMIZED:
								fprintf(stderr, "Window %d maximized\n", event.window.windowID);
								break;
							case SDL_WINDOWEVENT_RESTORED:
								fprintf(stderr, "Window %d restored\n", event.window.windowID);
								break;
							case SDL_WINDOWEVENT_ENTER:
								fprintf(stderr, "Mouse entered window %d\n",
										event.window.windowID);
								break;
							case SDL_WINDOWEVENT_LEAVE:
								fprintf(stderr, "Mouse left window %d\n", event.window.windowID);
								break;
							case SDL_WINDOWEVENT_FOCUS_GAINED:
								fprintf(stderr, "Window %d gained keyboard focus\n",
										event.window.windowID);
								break;
							case SDL_WINDOWEVENT_FOCUS_LOST:
								fprintf(stderr, "Window %d lost keyboard focus\n",
										event.window.windowID);
								break;
							case SDL_WINDOWEVENT_CLOSE:
								fprintf(stderr, "Window %d closed\n", event.window.windowID);

								it->refV8->NativeObject()->close();
								break;
						default:
							break;
						}

						break;
					}
				}
				break;
			default:
				break;
			}
		}
	}

	return runResult;
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