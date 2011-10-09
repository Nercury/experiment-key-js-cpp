#pragma once

#include <string>
#include <memory>
#include <map>
#include <list>
#include <key-common/types.h>
#include <key-common/error.hpp>
#include <key-window/lib_key_window.h>

namespace key {

	class Window;

	class Renderer
	{
	public:
		Renderer() {};
		virtual ~Renderer() {};
		/** Get renderer name to spit out in the face of some human */
		virtual std::string getName() = 0;
		/** Get true if screen saver is enabled */
		virtual bool isScreenSaverEnabled() = 0;
		/** Works globaly no matter on which window you call it - because all windows share the same renderer */
		virtual void setScreenSaverEnabled(bool value) = 0;
		/** Get the number of displays */
		virtual uint16_t getNumDisplays() = 0;
		/** Get display modes. Cram your modes into this list the way you like. Just know that
			on Javascript side, one will expect to get "width", "height" and probably "refreshRate".
			You can certainly add more stuff, but expect to parse it once you receive it in "setDesktopMode" call.
		*/
		virtual void getDisplayModes(uint16_t displayIndex, std::list<std::map<std::string, int32_t>> & modes) = 0;
		/**
			Return desktop mode. Usefull if one would like to set default full screen mode the same as
			desktop mode. After all, most users already have already configured their display settings the way
			they like. For desktop.
		*/
		virtual std::map<std::string, int32_t> getDesktopDisplayMode(uint16_t displayIndex) = 0;

		/**
			Add global renderer instance to available renderer list. Will be visible in window.renderDevices list on Javascript side. If your monitor is not so wide, I am sorry.
		*/
		LIB_KEY_WINDOW static void addRenderer(std::string identifier, std::shared_ptr<Renderer> instance);
		/**
			Get all those renderers as ineficiently as possible.
		*/
		LIB_KEY_WINDOW static std::map<std::string, std::shared_ptr<Renderer>> getRenderers();
	};

}