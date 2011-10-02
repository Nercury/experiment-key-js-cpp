#pragma once

#include <string>

#include <key-common/types.h>
#include <key-common/error.hpp>
#include <key-opengl/lib_key_opengl.h>
#include <key-window/Renderer.h>

namespace key {

	class OpenGL
		: public Renderer
	{
	private:
		static bool screenSaverEnabled;

	public:
		OpenGL() {};
		virtual ~OpenGL() {};
		virtual std::string getName() { return "OpenGL Render Device"; };
		LIB_KEY_OPENGL virtual fun_res_obj<DeviceInstance> createDevice(key::Window * window);
		LIB_KEY_OPENGL virtual bool isScreenSaverEnabled();
		LIB_KEY_OPENGL virtual void setScreenSaverEnabled(bool value);
		LIB_KEY_OPENGL virtual uint16_t getNumDisplays();

		static fun_res useSDL();
		static void unuseSDL();

		static void setGlobalSDLValues();
	};

}