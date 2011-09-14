#pragma once

#include <key-v8/BootStrapV8.h>

namespace key {

	class SubsystemBase {
	private:

	public:
		SubsystemBase() {};
		virtual ~SubsystemBase() {};
		virtual void initCore(v8::Handle<v8::Object> & dest) = 0;
	};

}