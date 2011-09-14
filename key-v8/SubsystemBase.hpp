#pragma once

#include <key-v8/expose_headers.hpp>

namespace key {

	class SubsystemBase {
	public:
		SubsystemBase() {};
		virtual ~SubsystemBase() {};
		virtual void initCore(v8::Handle<v8::Object> & dest) = 0;
	};

}