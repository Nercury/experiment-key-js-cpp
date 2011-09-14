#pragma once

#include <key-v8/BootStrapV8.h>

namespace key {

	class Scripting {
	private:

	public:
		Scripting() {};
		virtual ~Scripting() {};
		virtual void initCore(v8::Handle<v8::Object> & dest) = 0;
	};

}