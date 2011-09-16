#pragma once

#include <string>
#include <key-v8/expose_headers.hpp>

#include <SDL.h>
#include <key-window/lib_key_window.h>

namespace key {

	class Window
	{
	public:
		Window() : windowTitle("Key Window") { }
		LIB_KEY_WINDOW virtual ~Window();

		typedef cvv8::Signature<key::Window (
			cvv8::CtorForwarder<key::Window *()>
		)> Ctors;

		std::string windowTitle;
		void setWindowTitle(std::string newTitle);

		void run(const v8::Arguments & args);

		v8::Persistent<v8::Function> onWindowInit;
		v8::Handle<v8::Value> getOnWindowInit();
		void setOnWindowInit(v8::Handle<v8::Value> value);
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