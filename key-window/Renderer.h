#pragma once

#include <string>
#include <memory>
#include <map>
#include <list>
#include <key-common/types.h>
#include <key-common/error.hpp>
#include <key-window/lib_key_window.h>

namespace key {

	class DeviceInstance;
	class Window;

	class Renderer
	{
	public:
		Renderer() {};
		virtual ~Renderer() {};
		virtual std::string getName() = 0;
		virtual fun_res_obj<DeviceInstance> createDevice(key::Window * window) = 0;
		virtual bool isScreenSaverEnabled() = 0;
		virtual void setScreenSaverEnabled(bool value) = 0;
		virtual uint16_t getNumDisplays() = 0;
		virtual void getDisplayModes(uint16_t displayIndex, std::list<std::map<std::string, int32_t>> & modes) = 0;
		virtual std::map<std::string, int32_t> getDesktopDisplayMode(uint16_t displayIndex) = 0;

		LIB_KEY_WINDOW static void addRenderer(std::string identifier, std::shared_ptr<Renderer> instance);
		LIB_KEY_WINDOW static std::map<std::string, std::shared_ptr<Renderer>> getRenderers();
	};

}