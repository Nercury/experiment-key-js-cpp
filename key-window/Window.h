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
			"  width : an integer" "\n"
			"  height : an integer" "\n"
			"  refreshRate : an integer value for refresh rate in Hz" "\n"
			"}")
		std::list<std::map<std::string, int32_t>> getDisplayModes(uint16_t displayIndex);

		FLECT_GS(key::Window, displayMode, 
			Member, std::map<std::string GOOD_COMMA int32_t>, displayMode, 
			Method, void (v8::Handle<v8::Value>), setDisplayMode, 
			"map<string, int>", "Get or set current display mode")
		std::map<std::string, int32_t> displayMode; void setDisplayMode(v8::Handle<v8::Value> newMode);

		FLECT_GS(key::Window, fullScreen, 
			Member, bool, fullScreen, 
			Method, void (bool), setFullScreen, 
			"bool", "Get or set full screen mode")
		bool fullScreen; void setFullScreen(bool value);

		FLECT_GS(key::Window, hidden, 
			Member, bool, hidden, 
			Method, void (bool), setHidden, 
			"bool", "Hide or show the window")
		bool hidden; void setHidden(bool value);

		FLECT_GS(key::Window, resizable, 
			Member, bool, resizable, 
			Method, void (bool), setResizable, 
			"bool", "Window resizing is allowed")
		bool resizable; void setResizable(bool value);

		FLECT_GS(key::Window, minimized, 
			Member, bool, minimized, 
			Method, void (bool), setMinimized, 
			"bool", "Minimize or restore the window")
		bool minimized; void setMinimized(bool value);

		FLECT_GS(key::Window, maximized, 
			Member, bool, maximized, 
			Method, void (bool), setMaximized, 
			"bool", "Maximize or restore the window")
		bool maximized; void setMaximized(bool value);

		FLECT_GS(key::Window, inputGrabbed, 
			Member, bool, inputGrabbed, 
			Method, void (bool), setInputGrabbed, 
			"bool",  "Grab or ungrab mouse pointer (pointer is not allowed to move outside the window bounds when grabbed)")
		bool inputGrabbed; void setInputGrabbed(bool value);

		FLECT_GS(key::Window, windowSize, 
			Member, std::list<int32_t>, windowSize, 
			Method, void (std::list<int32_t>), setWindowSize, 
			"array<int>",  "Get or set window size. Size uses two integer values in array [width, height].")
		std::list<int32_t> windowSize; void setWindowSize(std::list<int32_t> value);

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

		static const int16_t NOTIFY_CHANGE_TITLE = 1;
		static const int16_t NOTIFY_CHANGE_DISPLAY_MODE = 2;
		static const int16_t NOTIFY_CHANGE_FULL_SCREEN = 3;
		static const int16_t NOTIFY_CHANGE_HIDDEN = 4;
		static const int16_t NOTIFY_CHANGE_RESIZABLE = 5;
		static const int16_t NOTIFY_CHANGE_MINIMIZED = 6;
		static const int16_t NOTIFY_CHANGE_MAXIMIZED = 7;
		static const int16_t NOTIFY_CHANGE_INPUT_GRAB = 8;
		static const int16_t NOTIFY_CHANGE_WINDOW_SIZE = 9;

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
			REFLECT(displayMode)
			REFLECT(fullScreen)
			REFLECT(hidden)
			REFLECT(resizable)
			REFLECT(minimized)
			REFLECT(maximized)
			REFLECT(inputGrabbed)
			REFLECT(windowSize)
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