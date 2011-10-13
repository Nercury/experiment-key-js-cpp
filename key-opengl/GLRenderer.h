#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <boost/date_time/posix_time/posix_time.hpp>

#include <key-opengl/SDLWindowInfo.h>
#include <key-window/Renderer.h>
#include <key-v8/PersistentV8.h>
#include <key-window/MouseMotion.h>
#include <key-window/KeyEvent.h>

namespace key {

	class GLRenderer
		: public Renderer
	{
	private:
		static bool screenSaverEnabled;
		std::vector<SDLWindowInfo> openedWindows;

		key::PersistentV8<key::MouseMotion> mouseMotion;
		key::PersistentV8<key::KeyEvent> keyEvent;

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