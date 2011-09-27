#pragma once

#include <string>
#include <GL3/gl3.h>

#include <SDL.h>
#include <key-common/types.h>
#include <key-opengl/lib_key_opengl.h>
#include <key-window/DeviceInstance.hpp>

namespace key {

	class OpenGLInstance
		: public DeviceInstance
	{
	private:
		SDL_Surface *surface;
		/*Uint32 sdl_flags;*/
		int videoFlags;
		int screenBpp;

		int16_t width;
		int16_t height;

		int16_t window_width;
		int16_t window_height;

		int16_t full_width;
		int16_t full_height;

		int16_t desktop_width;
		int16_t desktop_height;
	public:
		OpenGLInstance() {};
		virtual ~OpenGLInstance() {};
	};

}