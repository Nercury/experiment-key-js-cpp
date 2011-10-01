#include "OpenGL.h"

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
	if (window_instances == 0)
	{
		if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		{
			return fun_error(boost::format("Failed to initialize SDL: %1%") % SDL_GetError());
		} else {
			SDL_StartTextInput();
			OpenGL::setGlobalSDLValues();

			cout << "SDL " << SDL_MAJOR_VERSION << "." << SDL_MINOR_VERSION << "." << SDL_PATCHLEVEL << " initialized." << endl;
		}
		window_instances++;
	}
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