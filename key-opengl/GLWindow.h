#pragma once

#include <string>

#include <key-common/platform.hpp>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <key-common/types.h>
#include <key-opengl/lib_key_opengl.h>
#include <key-window/Window.h>

namespace key {

	class GLWindow
	{
	private:
		SDL_Window *sdl_window;
		SDL_GLContext context;
		key::Window * key_window;

		int32_t renderWidth;
		int32_t renderHeight;

		bool running;
		
		void resize();
		void handleEvent(SDL_Event &evt, int64_t dt);
		void update(int64_t dt);
		void render();
	public:
		GLWindow(key::Window * window);
		virtual ~GLWindow() { std::cout<< "Device destroyed." << std::endl; };
		LIB_KEY_OPENGL virtual fun_res run();
		LIB_KEY_OPENGL virtual void notifyWindowChange(int16_t window_change);
		LIB_KEY_OPENGL virtual void unsetWindow();
	};

}