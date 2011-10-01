#pragma once

#include <string>
#include <memory>
#include <map>
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

		LIB_KEY_WINDOW static void addRenderer(std::string identifier, std::shared_ptr<Renderer> instance);
		LIB_KEY_WINDOW static std::map<std::string, std::shared_ptr<Renderer>> getRenderers();
	};

}