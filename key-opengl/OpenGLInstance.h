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

		int32_t renderWidth;
		int32_t renderHeight;

		/*int16_t window_width;
		int16_t window_height;

		int16_t full_width;
		int16_t full_height;

		int16_t desktop_width;
		int16_t desktop_height;*/

		bool running;
		
		void resize();
		void handleEvent(SDL_Event &evt, int64_t dt);
		void update(int64_t dt);
		void render();
	public:
		OpenGLInstance(key::Window * window);
		virtual ~OpenGLInstance() { std::cout<< "Device destroyed." << std::endl; };
		LIB_KEY_OPENGL virtual fun_res run();
		LIB_KEY_OPENGL virtual void notifyWindowChange(int16_t window_change);
		LIB_KEY_OPENGL virtual void unsetWindow();
	};

}