#pragma once

#include <string>

#include <key-common/types.h>
#include <key-common/doc.hpp>
#include <key-v8/expose_headers.hpp>
#include <key-v8/reflect.hpp>
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

		FLECT_GS(key::Window, windowTitle, 
			Member, std::string, windowTitle, 
			Method, void (std::string), setWindowTitle, 
			"string", "Get or set window title")
		std::string windowTitle; void setWindowTitle(std::string newTitle);
	
		FLECT_G(key::Window, allRenderDevices,
			Member, std::vector<std::string>, allRenderDevices, 
			"array<string>", "Get all available render devices")
		std::vector<std::string> allRenderDevices;

		FLECT_GS(key::Window, onWindowInit, 
			Member, v8::Persistent<v8::Function>, onWindowInit, 
			Method, void (v8::Handle<v8::Value>), setOnWindowInit, 
			"function", "Set window initialization callback")
		v8::Persistent<v8::Function> onWindowInit; void setOnWindowInit(v8::Handle<v8::Value> value);

		FLECT_GS(key::Window, onWindowResize, 
			Member, v8::Persistent<v8::Function>, onWindowResize, 
			Method, void (v8::Handle<v8::Value>), setOnWindowResize, 
			"function", "Set window resize callback")
		v8::Persistent<v8::Function> onWindowResize; void setOnWindowResize(v8::Handle<v8::Value> value);

		FLECT_M(key::Window, run, void (), "void", "()", 
			"Create window loop and run the window." "\n"
			"Note: this call blocks until the window is closed.")
		void run();

		/* reflection */
		typedef cvv8::Signature<key::Window (
			cvv8::CtorForwarder<key::Window *()>
		)> Ctors;

		static void reflect(std::vector<std::string> & items, cvv8::ClassCreator<key::Window> & cc, 
			v8::Handle<v8::ObjectTemplate> proto, bool for_static) {
			REFLECT(windowTitle)
			REFLECT(allRenderDevices)
			REFLECT(onWindowInit)
			REFLECT(onWindowResize)
			REFLECT(run)
		}
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