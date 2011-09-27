#pragma once

#include <string>
#include <key-common/types.h>
#include <key-v8/expose_headers.hpp>
#include <key-window/lib_key_window.h>
#include <key-window/DeviceInstance.hpp>

namespace key {

	class Window
	{
	private:
		DeviceInstance * device;
	public:
		Window();
		LIB_KEY_WINDOW virtual ~Window();

		typedef cvv8::Signature<key::Window (
			cvv8::CtorForwarder<key::Window *()>
		)> Ctors;

		std::string windowTitle;
		void setWindowTitle(std::string newTitle);

		void run(const v8::Arguments & args);
		std::vector<std::string> allRenderDevices;

		v8::Persistent<v8::Function> onWindowInit; void setOnWindowInit(v8::Handle<v8::Value> value);
		v8::Persistent<v8::Function> onWindowResize; void setOnWindowResize(v8::Handle<v8::Value> value);
	};

}

namespace cvv8 {
    CVV8_TypeName_DECL((key::Window));

    template <>
    class ClassCreator_Factory<key::Window>
     : public ClassCreator_Factory_Dispatcher< key::Window,
          CtorArityDispatcher<key::Window::Ctors> >
    {};

    template <>
    struct JSToNative< key::Window > : JSToNative_ClassCreator< key::Window >
    {};
}