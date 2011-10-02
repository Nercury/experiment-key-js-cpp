#pragma once

#include <string>
#include <memory>
#include <list>
#include <map>

#include <key-common/types.h>
#include <key-v8/expose_headers.hpp>
#include <key-v8/reflect.hpp>
#include <key-window/lib_key_window.h>
#include <key-window/DeviceInstance.hpp>
#include <key-window/Renderer.h>

namespace key {

	class Window
		: public std::enable_shared_from_this<key::Window>
	{
	private:
		std::shared_ptr<DeviceInstance> device;

		std::map<std::string, std::shared_ptr<key::Renderer>> allRenderers;
		std::shared_ptr<key::Renderer> getCurrentRenderer();
	public:
		Window();
		LIB_KEY_WINDOW virtual ~Window();

		FLECT_GS(key::Window, windowTitle, 
			Member, std::string, windowTitle, 
			Method, void (std::string), setWindowTitle, 
			"string", "Get or set window title")
		std::string windowTitle; void setWindowTitle(std::string newTitle);

		FLECT_GS(key::Window, screenSaverEnabled, 
			Method, bool (), getScreenSaverEnabled, 
			Method, void (bool), setScreenSaverEnabled, 
			"bool", "Globally enable or disable screen saver")
		void setScreenSaverEnabled(bool value);
		bool getScreenSaverEnabled();
	
		FLECT_G(key::Window, numDisplays,
			Method, uint16_t (), getNumDisplays, 
			"uint16", "Get number of displays")
		uint16_t getNumDisplays();

		FLECT_M(key::Window, getDisplayModes, std::list<std::map<std::string GOOD_COMMA int32_t>>(uint16_t), "array<map<string, int>>", "(int displayIndex)", 
			"Get all available display modes for specified display." "\n"
			"Function returns arry of objects with following structure:" "\n"
			"{" "\n"
			"  width" "\n"
			"  height" "\n"
			"  refreshRate : an integer value for refresh rate in Hz" "\n"
			"}")
		std::list<std::map<std::string, int32_t>> getDisplayModes(uint16_t displayIndex);

		FLECT_G(key::Window, allRenderDevices,
			Member, std::vector<std::string>, allRenderDevices, 
			"array<string>", "Get all available render devices")
		std::vector<std::string> allRenderDevices;

		FLECT_PROP(key::Window, currentDevice, std::string,  
			"string", "Get or set current render device")
		std::string currentDevice;

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

		FLECT_M(key::Window, run, bool (), "bool", "()", 
			"Create window loop and run the window." "\n"
			"Note: this call blocks until the window is closed.")
		bool run();

		/* reflection */
		typedef cvv8::Signature<key::Window (
			cvv8::CtorForwarder<key::Window *()>
		)> Ctors;

		static void reflect(std::vector<std::string> & items, cvv8::ClassCreator<key::Window> & cc, 
			v8::Handle<v8::ObjectTemplate> proto, bool for_static) {
			REFLECT(windowTitle)
			REFLECT(screenSaverEnabled)
			REFLECT(numDisplays)
			REFLECT(getDisplayModes)
			REFLECT(allRenderDevices)
			REFLECT(currentDevice)
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