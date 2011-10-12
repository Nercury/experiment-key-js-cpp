#pragma once

#include <key-v8/expose_headers.hpp>
#include <key-v8/reflect.hpp>

#include <SDL2/SDL_keycode.h>

namespace key {

	struct Keycode
	{
	public:
		FLECT_PROP(key::Keycode, bLeft, bool, "bool", "Left button is pressed")
		bool bLeft;
		FLECT_PROP(key::Keycode, bMiddle, bool, "bool", "Middle button is pressed")
		bool bMiddle;
		FLECT_PROP(key::Keycode, bRight, bool, "bool", "Right button is pressed")
		bool bRight;
		FLECT_PROP(key::Keycode, bX1, bool, "bool", "Extra 1 button is pressed")
		bool bX1;

		/* reflection */
		typedef cvv8::Signature<key::Keycode (
			cvv8::CtorForwarder<key::Keycode *()>
		)> Ctors;

		static void reflect(std::vector<std::string> & items, cvv8::ClassCreator<key::Keycode> & cc, 
			v8::Handle<v8::ObjectTemplate> proto, bool for_static) {

				int sc = SDL_SCANCODE_0;

			REFLECT(bLeft)
			REFLECT(bMiddle)
			REFLECT(bRight)
			REFLECT(bX1)
		}
	};
}

namespace cvv8 {
    CVV8_TypeName_DECL((key::Keycode));

    template <>
    class ClassCreator_Factory<key::Keycode>
     : public ClassCreator_Factory_Dispatcher< key::Keycode,
          CtorArityDispatcher<key::Keycode::Ctors> >
    {};

    template <>
    struct JSToNative< key::Keycode > : JSToNative_ClassCreator< key::Keycode >
    {};
}