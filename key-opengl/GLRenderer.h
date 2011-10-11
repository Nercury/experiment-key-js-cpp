#pragma once

#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <key-common/types.h>
#include <key-common/error.hpp>
#include <key-opengl/lib_key_opengl.h>
#include <key-window/Renderer.h>
#include <key-v8/KeyV8.h>
#include <key-window/Window.h>

namespace key {

	class SDLWindowInfo
	{
	public:
		SDLWindowInfo() : sdl_window(NULL), context(0) {}
		~SDLWindowInfo() {}

		std::shared_ptr<key::PersistentV8<key::Window>> refV8;
		SDL_Window *sdl_window;
		SDL_GLContext context;
	};

	class GLRenderer
		: public Renderer
	{
	private:
		static bool screenSaverEnabled;
		std::unordered_map<uint64_t, SDLWindowInfo> openedWindows;
	public:
		GLRenderer() {};
		virtual ~GLRenderer() {};
		virtual std::string getName() { return "OpenGL Render Device"; };
		LIB_KEY_OPENGL virtual bool isScreenSaverEnabled();
		LIB_KEY_OPENGL virtual void setScreenSaverEnabled(bool value);
		LIB_KEY_OPENGL virtual uint16_t getNumDisplays();
		LIB_KEY_OPENGL virtual void getDisplayModes(uint16_t displayIndex, std::list<std::map<std::string, int32_t>> & modes);
		LIB_KEY_OPENGL virtual std::map<std::string, int32_t> getDesktopDisplayMode(uint16_t displayIndex);

		virtual bool addWindow(v8::Handle<v8::Object> v8_window);
		virtual bool removeWindow(uint64_t id);
		virtual bool runWindowLoop();

		static fun_res useSDL();
		static void unuseSDL();

		static bool parseDisplayMode(std::map<std::string, int32_t> modeValues, int & w, int & h, int & refreshRate);
		static void setGlobalSDLValues();
	};

}