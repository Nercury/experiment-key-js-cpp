#pragma once

#include <memory>
#include <key-common/types.h>
#include <key-common/error.hpp>

namespace key {

	class DeviceInstance
	{
	public:
		DeviceInstance() {};
		virtual ~DeviceInstance() {};
		virtual fun_res run() = 0;
		virtual void notifyWindowChange(int16_t window_change) = 0;
		virtual void unsetWindow() = 0;
	};

}