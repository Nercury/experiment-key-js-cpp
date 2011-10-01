#pragma once

#include <memory>
#include <key-common/error.hpp>

namespace key {

	class DeviceInstance
	{
	public:
		DeviceInstance() {};
		virtual ~DeviceInstance() {};
		virtual fun_res run() = 0;
		virtual void notifyWindowChange() = 0;
	};

}