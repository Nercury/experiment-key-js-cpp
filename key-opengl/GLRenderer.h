#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <boost/date_time/posix_time/posix_time.hpp>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <key-common/types.h>
#include <key-common/error.hpp>
#include <key-opengl/lib_key_opengl.h>
#include <key-window/Renderer.h>
#include <key-v8/PersistentV8.h>
#include <key-window/Window.h>
#include <key-window/MouseMotion.h>

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
	};

	class GLRenderer
		: public Renderer
	{
	private:
		static bool screenSaverEnabled;
		std::vector<SDLWindowInfo> openedWindows;

		key::PersistentV8<key::MouseMotion> mouseMotion;

		// used to notify window loop about a closed window
		bool windowRemoved;

		bool createWindow(SDLWindowInfo & wi);
		void destroyWindow(SDLWindowInfo & wi);
		void unuseSdlIfNoWindows();
	public:
		GLRenderer();
		virtual ~GLRenderer() {};
		virtual std::string getName() { return "OpenGL Render Device"; };
		LIB_KEY_OPENGL virtual bool isScreenSaverEnabled();
		LIB_KEY_OPENGL virtual void setScreenSaverEnabled(bool value);
		LIB_KEY_OPENGL virtual uint16_t getNumDisplays();
		LIB_KEY_OPENGL virtual void getDisplayModes(uint16_t displayIndex, std::list<std::map<std::string, int32_t>> & modes);
		LIB_KEY_OPENGL virtual std::map<std::string, int32_t> getDesktopDisplayMode(uint16_t displayIndex);

		virtual bool addWindow(v8::Handle<v8::Object> v8_window);
		virtual bool removeWindow(uint64_t id);
		virtual bool runWindowLoop(v8::Handle<v8::Context> context);

		static fun_res useSDL();
		static void unuseSDL();

		static bool parseDisplayMode(std::map<std::string, int32_t> modeValues, int & w, int & h, int & refreshRate);
		static void setGlobalSDLValues();
	};

}