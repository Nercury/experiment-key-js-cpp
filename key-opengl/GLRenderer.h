#pragma once

#include <string>

#include <key-common/types.h>
#include <key-common/error.hpp>
#include <key-opengl/lib_key_opengl.h>
#include <key-window/Renderer.h>

namespace key {

	class GLRenderer
		: public Renderer
	{
	private:
		static bool screenSaverEnabled;

	public:
		GLRenderer() {};
		virtual ~GLRenderer() {};
		virtual std::string getName() { return "OpenGL Render Device"; };
		LIB_KEY_OPENGL virtual bool isScreenSaverEnabled();
		LIB_KEY_OPENGL virtual void setScreenSaverEnabled(bool value);
		LIB_KEY_OPENGL virtual uint16_t getNumDisplays();
		LIB_KEY_OPENGL virtual void getDisplayModes(uint16_t displayIndex, std::list<std::map<std::string, int32_t>> & modes);
		LIB_KEY_OPENGL virtual std::map<std::string, int32_t> getDesktopDisplayMode(uint16_t displayIndex);

		static fun_res useSDL();
		static void unuseSDL();

		static bool parseDisplayMode(std::map<std::string, int32_t> modeValues, int & w, int & h, int & refreshRate);
		static void setGlobalSDLValues();
	};

}