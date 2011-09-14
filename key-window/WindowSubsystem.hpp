#pragma once

#include <key-v8/Scripting.hpp>

namespace key {

	class WindowSubsystem
		: public key::Scripting
	{
	private:
	public:
		virtual void initCore(v8::Handle<v8::Object> & dest) {
			std::cout<< "Test" << std::endl;
		}
	};

}