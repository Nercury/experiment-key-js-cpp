#pragma once

#include <memory>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <key-common/types.h>
#include <key-common/error.hpp>
#include <key-opengl/lib_key_opengl.h>
#include <key-window/Window.h>
#include <key-v8/PersistentV8.h>

namespace key {

	class SDLWindowInfo
	{
	public:
		SDLWindowInfo() : sdlWindow(NULL), context(0), renderWidth(800), renderHeight(600), sdlWindowID(0), hasKeyboardFocus(false), hasMouseFocus(false) {}
		SDLWindowInfo(std::shared_ptr<key::PersistentV8<key::Window>> & refV8) : refV8(refV8), sdlWindow(NULL), context(0) {}
		~SDLWindowInfo() {}

		int32_t renderWidth;
		int32_t renderHeight;

		uint32_t sdlWindowID;
		bool hasKeyboardFocus;
		bool hasMouseFocus;

		std::shared_ptr<key::PersistentV8<key::Window>> refV8;
		SDL_Window *sdlWindow;
		SDL_GLContext context;

		void makeCurrent();
		void resize();
		void render();
	};

}