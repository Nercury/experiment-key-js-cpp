#pragma once

#include <string>

#include <key-common/platform.hpp>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <key-common/types.h>
#include <key-opengl/lib_key_opengl.h>
#include <key-window/DeviceInstance.hpp>
#include <key-window/Window.h>

namespace key {

	class OpenGLInstance
		: public DeviceInstance
	{
	private:
		SDL_Window *sdl_window;
		SDL_GLContext context;
		key::Window * key_window;
		
		/*Uint32 sdl_flags;*/
		/*int videoFlags;
		int screenBpp;*/

		int16_t width;
		int16_t height;

		/*int16_t window_width;
		int16_t window_height;

		int16_t full_width;
		int16_t full_height;

		int16_t desktop_width;
		int16_t desktop_height;*/
	public:
		OpenGLInstance(key::Window * window);
		virtual ~OpenGLInstance() {};
		LIB_KEY_OPENGL virtual fun_res run();
		LIB_KEY_OPENGL virtual void notifyWindowChange();
	};

}