#pragma once

#include <key-window/lib_key_window.h>
#include <key-v8/SubsystemBase.hpp>

namespace key {

	class SsWindow
		: public key::SubsystemBase
	{
	private:
	public:
		SsWindow() {};
		virtual ~SsWindow() {};
		LIB_KEY_WINDOW virtual void initCore(v8::Handle<v8::Object> & dest);
	};

}