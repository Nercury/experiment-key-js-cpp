#pragma once

#include <boost/format.hpp>
#include <boost/function.hpp>
#include <key-v8/expose_headers.hpp>
#include <key-v8/reflect.hpp>

#include <SDL2/SDL.h>

namespace key {

	struct KeyEvent
	{
	public:
		FLECT_PROP(key::KeyEvent, keyCode, int32_t, "int", "Virtual key code. Use Keycode enumeration to compare values.")
		int32_t keyCode;
		FLECT_PROP(key::KeyEvent, scanCode, uint16_t, "int", "Physical key code. Use Scancode enumeration to compare values.")
		uint16_t scanCode;
		FLECT_PROP(key::KeyEvent, mod, uint16_t, "int", "Current key modifiers (Ctrl, Alt, Shift).")
		uint16_t mod;

		// assign to this function callback to get human-readable name for a key code
		boost::function<std::string (int32_t)> onGetKeyName;

		FLECT_M(key::KeyEvent, getVk, std::string (), "string", "()", 
			"Get string for virtual key code (if not available, returns false).")
		std::string getVk() { 
			return keyCode == SDLK_UNKNOWN ? "" : (boost::format("%1%") % keyCode).str();
		} 

		FLECT_M(key::KeyEvent, getVkName, std::string (), "string", "()", 
			"Use this function to get a human-readable name for a key.")
		std::string getVkName() { 
			if (onGetKeyName) {
				return keyCode == SDLK_UNKNOWN ? "" : std::string(onGetKeyName(keyCode));
			} else {
				return "Unknown Name";
			}
		} 

		/* reflection */
		typedef cvv8::Signature<key::KeyEvent (
			cvv8::CtorForwarder<key::KeyEvent *()>
		)> Ctors;

		static void reflect(std::vector<std::string> & items, cvv8::ClassCreator<key::KeyEvent> & cc, 
			v8::Handle<v8::ObjectTemplate> proto, bool for_static) {

			REFLECT(keyCode)
			REFLECT(scanCode)
			REFLECT(mod)
			REFLECT(getVk)
			REFLECT(getVkName)
		}
	};
}

namespace cvv8 {
    CVV8_TypeName_DECL((key::KeyEvent));

    template <>
    class ClassCreator_Factory<key::KeyEvent>
     : public ClassCreator_Factory_Dispatcher< key::KeyEvent,
          CtorArityDispatcher<key::KeyEvent::Ctors> >
    {};

    template <>
    struct JSToNative< key::KeyEvent > : JSToNative_ClassCreator< key::KeyEvent >
    {};
}